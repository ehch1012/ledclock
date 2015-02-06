#ifndef CLOCK_WHITE_MODE_h
#define CLOCK_WHITE_MODE_h

#include "Arduino.h"
#include "FastLED.h"
#include "ClockMode.h"

class GlowMode : public ClockMode {
  
private:
  void init(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor, boolean secondsFilling);

  boolean secondsFillingActive = false;
  boolean secondsFilling = true;
  int lastSecond = 0;
  
protected: 
  void showQuaters(CRGB leds[]);
  void showSeconds(CRGB leds[]);
  void showMinutes(CRGB leds[]);
  void showHours(CRGB leds[]);

 

public:
  GlowMode();
  GlowMode(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor);
  GlowMode(CHSV backgroundColor, CHSV secondPointerColor, CHSV minutePointerColor, CHSV hourPointerColor, CHSV quaterColor, boolean secondsFilling);
  virtual void setDisplay(CRGB leds[]);
};



#endif
