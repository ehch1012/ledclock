 #ifndef CLOCK_MODE_h
#define CLOCK_MODE_h

#include "Arduino.h"
#include "FastLED.h"


class ClockMode {
protected:
  const byte hourPins[12] = {0,5,10,15,20,25,30,35,40,45,50,55};  
  boolean setMode = false;
  void glow(CRGB leds[], int pos, CHSV color);
  void glow(CRGB leds[], int pos, CHSV color, int level);
  int calcLight(float base);
  int calcLight(float base, int minLight);
  void fadeColor(CHSV& color);
  void fadeColor(CHSV& color, int minLight);
  
  CHSV backgroundColor = CHSV(0, 0, 0);
  CHSV secondPointerColor = CHSV(0, 0, 150);
  CHSV minutePointerColor = CHSV(0, 0, 180);
  CHSV hourPointerColor = CHSV(0, 0, 255);
  CHSV quaterColor = CHSV(96, 150, 180);
   
private: 
    
  int lightFactor;
  
public:
  virtual void setDisplay(CRGB leds[]);
  void setTimeMode(boolean active);
  void setLightFactor(int value);
};
#endif


