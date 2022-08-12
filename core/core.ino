/*
   l9_light_alpha
   by far-galaxy
*/

#define DEBUG 1

#include <FastLED.h>
#include "core_utils.h"
#include "buildTime.h"

#define LED_PIN D5
#define NUM_LEDS 12
CRGB leds[NUM_LEDS];

Time t;

void setup() {
#if DEBUG
  Serial.begin(115200);
#endif
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  t.hour = BUILD_HOUR;
  t.minute = BUILD_MIN;
  t.second = BUILD_SEC;
  t.ms = 0;
}

unsigned long timer = 0;

void loop() {

  unsigned long now = millis();

  if (now - timer > 40) {
    timer = now;
    
    t.ms += 40;

    if (t.ms >= 1000) {
      t.second++;
      t.ms = 0;
    }
    if (t.second >= 60) {
      t.minute++;
      t.second = 0;
    }
    if (t.minute >= 60) {
      t.hour++;
      t.minute = 0;
    }
    
    log(t.hour); log("\t"); log(t.minute); log("\t"); logln(t.second);
    ledClock(t);
    FastLED.show();
  }
}
