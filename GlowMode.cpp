#include "Arduino.h"
#include "GlowMode.h"
#include "Time.h"

#define NUM_LEDS 60

GlowMode::GlowMode() {}
GlowMode::GlowMode(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor) {
 init(backgroundColor, secondPointerColor, minutePointerColor, hourPointerColor, quaterColor, false);
}

GlowMode::GlowMode(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor, boolean secondsFilling) {
  init(backgroundColor, secondPointerColor, minutePointerColor, hourPointerColor, quaterColor, secondsFilling);
}

void GlowMode::init(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor, boolean secondsFilling) {
 this->backgroundColor = backgroundColor;
 this->secondPointerColor = secondPointerColor;
 this->minutePointerColor = minutePointerColor;
 this->hourPointerColor = hourPointerColor;
 this->quaterColor = quaterColor;
 this->secondsFillingActive = secondsFilling;
}

void GlowMode::setDisplay(CRGB leds[]){

  if(!secondsFillingActive) { 
    CHSV color = backgroundColor;
    fadeColor(color,0);
    fill_solid(leds, NUM_LEDS, color);
  }
  showQuaters(leds);
  showSeconds(leds);
  showMinutes(leds);
  showHours(leds);
}

void GlowMode::showQuaters(CRGB leds[]){
  CHSV color = quaterColor;
  fadeColor(color);
  
  leds[hourPins[0]] = color;
  leds[hourPins[3]] = color;
  leds[hourPins[6]] = color;
  leds[hourPins[9]] = color;
  glow(leds,hourPins[0],color,2);
  glow(leds,hourPins[3],color,2);
  glow(leds,hourPins[6],color,2);
  glow(leds,hourPins[9],color,2);  
  
  if(setMode && (millis()/1000)%2) {
    color = backgroundColor;
    fadeColor(color);
    leds[hourPins[0]] = color;
    leds[hourPins[3]] = color;
    leds[hourPins[6]] = color;
    leds[hourPins[9]] = color;
  }
}

void GlowMode::showSeconds(CRGB leds[]){
  int currentSecond = second(); 
  
  CHSV secondsColor = secondPointerColor;
  fadeColor(secondsColor);
    
  if(secondsFillingActive) {
    CHSV bgColor = backgroundColor;
    fadeColor(bgColor,0);
    
    secondsFilling = (currentSecond == 0 && currentSecond != lastSecond) ? !secondsFilling : secondsFilling;
    
    if(secondsFilling) {
      fill_solid(leds, NUM_LEDS, bgColor);
      fill_solid(leds, currentSecond, secondsColor);
    } else {
      fill_solid(leds, NUM_LEDS, secondsColor);
      fill_solid(leds, currentSecond, bgColor);
    } 
    
    lastSecond = currentSecond;
  } else {
    leds[currentSecond] = secondsColor;
  }
  
}

void GlowMode::showMinutes(CRGB leds[]){
  int currentMinute = minute();
  CHSV color = minutePointerColor;
  fadeColor(color);
  leds[currentMinute] = color;
  
}
void GlowMode::showHours(CRGB leds[]){
  int currentHour = hour();
  int currentMinute = minute();
  
  int hourPin = hourPins[currentHour%12];
  
 // if(currentMinute >= 12) hourPin++;
 // if(currentMinute >= 24) hourPin++;
 // if(currentMinute >= 36) hourPin++;
 // if(currentMinute >= 48) hourPin++;
  
  CHSV color = hourPointerColor;
  fadeColor(color);
  
  leds[hourPin] = color;

}

