#pragma once
#include <Arduino.h>
#include <FastLED.h>

#ifndef NUM_LEDS
#define NUM_LEDS 12
#endif

#ifndef PIN_LEDS
#define PIN_LEDS D5
#endif

class LED {
  public:
    LED();
    int bright = 0;
    CRGB points[NUM_LEDS];
    CRGB end[NUM_LEDS];
    void clock(Time &t);
    void fill(CRGB color);
    byte gammaCor(byte c);
    void tick();
    void setPoint(byte num, CRGB color);
    void show();
};

const uint8_t CRTgamma[256] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 5,
  5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 8,
  9, 10, 10, 10, 10, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 14,
  15, 15, 15, 16, 17, 17, 17, 17, 18, 18, 19, 20, 20, 20, 20, 21,
  22, 22, 23, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 30,
  30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 37, 37, 38, 38, 39, 40,
  41, 41, 42, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 53,
  54, 54, 55, 56, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67,
  68, 69, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84,
  85, 86, 87, 89, 90, 91, 93, 94, 95, 96, 97, 98, 100, 101, 102, 103,
  105, 106, 108, 109, 110, 111, 113, 115, 117, 118, 119, 121, 122, 123, 124, 127,
  128, 130, 131, 133, 134, 136, 137, 139, 140, 143, 145, 146, 147, 148, 151, 153,
  154, 156, 158, 159, 162, 163, 165, 167, 169, 171, 173, 174, 176, 179, 180, 182,
  185, 186, 188, 190, 192, 194, 196, 199, 201, 202, 205, 207, 209, 211, 214, 216,
  218, 220, 223, 225, 226, 230, 231, 235, 236, 240, 241, 245, 246, 250, 251, 255
};

LED::LED() {
  FastLED.addLeds<WS2812B, PIN_LEDS, GRB>(points, NUM_LEDS);
  FastLED.setBrightness(255);
}

void LED::clock(Time &t)
{
  fill(CRGB(0, 0, 0));

  end[0] = CRGB(1, 1, 1);

  end[t.hour % 12] += CRGB(125, 0, 0);

  end[t.minute / 5] += CRGB(0, gammaCor( 150 - ((t.minute % 5) * 60 + t.second) / 2 ), 0);
  end[(t.minute / 5 + 1) % 12] += CRGB(0, gammaCor(((t.minute % 5) * 60 + t.second) / 2), 0);

  end[t.second / 5] += CRGB(0, 0, gammaCor( 125 - ((t.second % 5) * 1000 + t.ms) / 40 ));
  end[(t.second / 5 + 1) % 12] += CRGB(0, 0, gammaCor(((t.second % 5) * 1000 + t.ms) / 40));
}

void LED::fill(CRGB color)
{
  ALL(d) {
    setPoint(d, color);
  }
}

byte LED::gammaCor(byte c)
{
  return (pgm_read_byte(&CRTgamma[c]));
}

#define MOVE(r) if (points[d].r < end[d].r) points[d].r++; else if (points[d].r > end[d].r) points[d].r--;

void LED::tick()
{
  ALL(d) {
    MOVE(r)
    MOVE(g)
    MOVE(b)
  }
  show();
}

void LED::setPoint(byte num, CRGB color)
{
  end[num] = CRGB(gammaCor(color.r),
                  gammaCor(color.g),
                  gammaCor(color.b));
}

void LED::show()
{
  FastLED.show();
}
