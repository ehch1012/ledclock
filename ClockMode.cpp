#include "Arduino.h"
#include "ClockMode.h"

#define NUM_LEDS 60

void ClockMode::setDisplay(CRGB leds[]){}
void ClockMode::setTimeMode(boolean active){this->setMode=active;}

void ClockMode::glow(CRGB leds[], int pos, CHSV color){
  glow(leds,pos,color,1);
}

void ClockMode::glow(CRGB leds[], int pos, CHSV color, int level){
  int before = pos-1;
  before = before<0 ? NUM_LEDS-1 : before;
  
  int after = pos+1;
  after = after > NUM_LEDS-1 ? 1 : after;
  
  color.v = color.v/2;
  leds[before] = color;
  leds[after] = color;
  
  for(int i=0; i<level-1&&color.v>40;i++) {
    before--;
    before = before<0 ? NUM_LEDS-1 : before;
    
    after++;
    after = after > NUM_LEDS-1 ? 1 : after;
    
    color.v = color.v/2;
    leds[before] = color;
    leds[after] = color;
  }
}

int ClockMode::calcLight(float base) {
   return calcLight(base, 20);
}

int ClockMode::calcLight(float base, int minLight) {
   base = base>2.55?2.55:base;   
   int val = base*lightFactor;
   val = val<minLight?minLight:val;
   
   return val;
}

void ClockMode::fadeColor(CHSV& color) {
  color.v = calcLight((float)color.v/(float)100);
}
void ClockMode::fadeColor(CHSV& color, int minLight) {
  color.v = calcLight((float)color.v/(float)100,minLight);
}

void ClockMode::setLightFactor(int value) {
  lightFactor = value > 100 ? 100 : value<=0 ? 1 : value;
}
