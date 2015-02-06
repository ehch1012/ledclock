
#include "Arduino.h"
#include "Clock.h"


static uint32_t provideRTCTime() {
 return RTC.now().get() + 946707779;
}

Clock::Clock() {
  Wire.begin();
  RTC.begin();
  setSyncProvider(provideRTCTime);
  
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 
 // BACKGROUND, SECONDS, MINUTES, HOURS, QUATERS
  modes[0] = new GlowMode(CHSV(0, 0, 30),CHSV(0,0,100),CHSV(0,0,160),CHSV(0,0,255),CHSV(0, 0, 125));
  modes[1] = new GlowMode(CHSV(0, 0, 30),CHSV(0,0,100),CHSV(0,0,160),CHSV(0,0,255),CHSV(0, 0, 125),true);
  modes[2] = new GlowMode(CHSV(32, 0, 30),CHSV(32,100,100),CHSV(32,125,160),CHSV(32,160,255),CHSV(32, 255, 125));
  modes[3] = new GlowMode(CHSV(32, 0, 30),CHSV(32,100,100),CHSV(32,125,160),CHSV(32,160,255),CHSV(32, 255, 125),true);
  modes[4] = new GlowMode(CHSV(64, 0, 30),CHSV(64,100,100),CHSV(64,125,160),CHSV(64,160,255),CHSV(64, 255, 125));
  modes[5] = new GlowMode(CHSV(64, 0, 30),CHSV(64,100,100),CHSV(64,125,160),CHSV(64,160,255),CHSV(64, 255, 125),true);
  modes[6] = new GlowMode(CHSV(96, 0, 30),CHSV(96,100,100),CHSV(96,125,160),CHSV(96,160,255),CHSV(96, 255, 125));
  modes[7] = new GlowMode(CHSV(96, 0, 30),CHSV(96,100,100),CHSV(96,125,160),CHSV(96,160,255),CHSV(96, 255, 125),true);
  modes[8] = new GlowMode(CHSV(128, 0, 30),CHSV(128,100,100),CHSV(128,125,160),CHSV(128,160,255),CHSV(128, 255, 125));
  modes[9] = new GlowMode(CHSV(128, 0, 30),CHSV(128,100,100),CHSV(128,125,160),CHSV(128,160,255),CHSV(128, 255, 125),true);
  modes[10] = new GlowMode(CHSV(160, 0, 30),CHSV(160,100,100),CHSV(160,125,160),CHSV(160,160,255),CHSV(160, 255, 125));
  modes[11] = new GlowMode(CHSV(160, 0, 30),CHSV(160,100,100),CHSV(160,125,160),CHSV(160,160,255),CHSV(160, 255, 125),true);
  modes[12] = new GlowMode(CHSV(192, 0, 30),CHSV(192,100,100),CHSV(192,125,160),CHSV(192,160,255),CHSV(192, 255, 125));
  modes[13] = new GlowMode(CHSV(192, 0, 30),CHSV(192,100,100),CHSV(192,125,160),CHSV(192,160,255),CHSV(192, 255, 125),true);
  modes[14] = new GlowMode(CHSV(224, 0, 30),CHSV(224,100,100),CHSV(224,125,160),CHSV(0,160,255),CHSV(224, 255, 125));
  modes[15] = new GlowMode(CHSV(224, 0, 30),CHSV(224,100,100),CHSV(224,125,160),CHSV(0,160,255),CHSV(224, 255, 125),true);
  modes[16] = new GlowMode(CHSV(0, 0, 30),CHSV(0,100,100),CHSV(0,125,160),CHSV(0,160,255),CHSV(0, 255, 125));
  modes[17] = new GlowMode(CHSV(0, 0, 30),CHSV(0,100,100),CHSV(0,125,160),CHSV(0,160,255),CHSV(0, 255, 125),true);
  
  tick();
}


    
void Clock::tick() {
 
 if(setMode) {
   setTime(hour(),minute(),0,year(),month(),day());   
 } 
  
 getCurrentMode()->setDisplay(leds);

 FastLED.show();
}

ClockMode* Clock::getCurrentMode() {
  return modes[currentMode%NUM_MODES];
}

void Clock::buttonSetTimeChanged(boolean pressed){
  setMode = pressed;
  getCurrentMode()->setTimeMode(pressed); 
  if(!pressed) {
   
   setTime(hour(),minute(),0,year(),month(),day());
   DateTime now = DateTime(year(),month(),day(),hour(),minute(),0);
   RTC.adjust(now);   
  }
}
void Clock::buttonSetHourChanged(boolean pressed){
  if(setMode && pressed) {
    setTime(hour()+1,minute(),0,year(),month(),day()); 
  }
}
void Clock::buttonSetMinuteChanged(boolean pressed){
  if(setMode && pressed) {
   setTime(hour(),minute()+1,0,year(),month(),day());
  }
}

void Clock::buttonSetModeChanged(boolean pressed){
 if(pressed) {
   currentMode++; 
 }
}
void Clock::setLightValue(int value) {
  lightValue = value>1000?1000:value<=0?1:value; 
  getCurrentMode()->setLightFactor(lightValue/10);
}

