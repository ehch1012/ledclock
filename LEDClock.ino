
#include "FastLED.h"
#include <Wire.h>
#include <RTClib.h>
#include "Clock.h"
#include "ClockMode.h"
#include "GlowMode.h"
#include "Time.h"



#define SET_TIME_BUTTON 9
#define HOUR_BUTTON 8
#define MINUTE_BUTTON 7
#define SET_MODE_BUTTON 6
#define SENSOR_LIGHT A0


Clock *c;

const int buttonCheckInterval = 1000;
boolean setTimeModePressed = false;
boolean hourButtonPressed = false;
boolean minuteButtonPressed = false;
boolean setClockModePressed = false;

int sensorValueCount = 0;
long lightValue=0;


void setup() {

  pinMode(SET_TIME_BUTTON, INPUT_PULLUP);
  pinMode(HOUR_BUTTON, INPUT_PULLUP);
  pinMode(MINUTE_BUTTON, INPUT_PULLUP);
  pinMode(SET_MODE_BUTTON, INPUT_PULLUP);
  pinMode(SENSOR_LIGHT, INPUT);

  c =  new Clock();
  c->setLightValue(analogRead(SENSOR_LIGHT));

}

void loop() {
  delay(20);
  
  checkButtons();
  checkLight();  
  
  c->tick(); 
}

void checkLight() {
  lightValue += analogRead(SENSOR_LIGHT);  
  sensorValueCount++;
  
  if(sensorValueCount >= 50) {
    c->setLightValue(lightValue/50); 
    sensorValueCount = 0; 
    lightValue=0;
  }
  
}

void checkButtons() {
  
  if(!setTimeModePressed && LOW == digitalRead(SET_TIME_BUTTON)) {
    setTimeModePressed = true;
    c->buttonSetTimeChanged(true);
  }
  if(setTimeModePressed && HIGH == digitalRead(SET_TIME_BUTTON)) {
    setTimeModePressed = false;    
    c->buttonSetTimeChanged(false);
  }   
 
  if(!hourButtonPressed && LOW == digitalRead(HOUR_BUTTON)) {
    hourButtonPressed = true;
    c->buttonSetHourChanged(true);
  }
  if(hourButtonPressed && HIGH == digitalRead(HOUR_BUTTON))  {
    hourButtonPressed = false;  
    c->buttonSetHourChanged(false);  
  } 
 
  if(!minuteButtonPressed && LOW == digitalRead(MINUTE_BUTTON)) {
    minuteButtonPressed = true;
    c->buttonSetMinuteChanged(true);
  } 
  if(minuteButtonPressed && HIGH == digitalRead(MINUTE_BUTTON)) {
    minuteButtonPressed = false;   
    c->buttonSetMinuteChanged(false); 
  } 
 
  if(!setClockModePressed && LOW == digitalRead(SET_MODE_BUTTON)) {
    setClockModePressed = true;
    c->buttonSetModeChanged(true);
  }
  if(setClockModePressed && HIGH == digitalRead(SET_MODE_BUTTON)) {
    setClockModePressed = false;   
    c->buttonSetModeChanged(false); 
  }  
}

