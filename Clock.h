#ifndef CLOCK_h
#define CLOCK_h
#include <Wire.h>
#include <RTClib.h>
#include "Arduino.h"
#include "Time.h"
#include "FastLED.h"
#include "ClockMode.h"
#include "GlowMode.h"

#define LED_PIN 5
#define NUM_LEDS 60
#define NUM_MODES 9

const RTC_DS1307 RTC;

class Clock {
 
private: 
  
  
  ClockMode *modes[NUM_MODES];  
  boolean setMode = false;
  CRGB leds[NUM_LEDS];
  int currentMode=0;
  int lightValue=1000;
  
  
  ClockMode* getCurrentMode();
  
public:
  Clock();
   
  void tick();

  void buttonSetTimeChanged(boolean pressed);
  void buttonSetHourChanged(boolean pressed);
  void buttonSetMinuteChanged(boolean pressed);
  void buttonSetModeChanged(boolean pressed);
  void setLightValue(int value);
  time_t syncProvider();
};



#endif
