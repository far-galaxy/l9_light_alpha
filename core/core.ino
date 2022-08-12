/*
   l9_light_alpha
   by far-galaxy
*/

#define DEBUG 0

#include <FastLED.h>
#define LED_PIN D5
#define NUM_LEDS 12
CRGB leds[NUM_LEDS];

void setup() {
  #if DEBUG
  Serial.begin(115200);
  #endif
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
}

byte b = 0;

void loop() {
  while (b < 255) {
    ledFill(CRGB(0, b, b));
    b++;
    delay(100);
  }
  while (b > 0) {
    ledFill(CRGB(0, b, b));
    b--;
    delay(100);
  }
}
