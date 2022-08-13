/*
   l9_light_alpha
   by far-galaxy
*/

#define DEBUG 1

#include "core_utils.h"
#include "led_utils.h"
#include "buildTime.h"
#include <GyverTM1637.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "LT100D_5556";
const char *password = "pswd";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600 * 3);

CRGB leds[NUM_LEDS];

GyverTM1637 disp(D1, D2);

Time t;
LED led;

void setup() {
#if DEBUG
  Serial.begin(115200);
#endif

  disp.clear();
  disp.brightness(7);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED )
  {
    delay ( 500 );
    log ( "." );
  }
  logln( "!!!" );
  timeClient.begin();
  timeClient.update();

  t.hour = timeClient.getHours();
  t.minute = timeClient.getMinutes();
  t.second = timeClient.getSeconds();
  t.ms = 0;
}

unsigned long timer = 0;

void loop() {

  unsigned long now = millis();

  if (now - timer >= 40) {
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
      t.hour %= 24;
      t.minute = 0;
    }

    log(t.hour); log("\t"); log(t.minute); log("\t"); logln(t.second);
    led.clock(t);
    disp.displayClock(t.hour, t.minute);
    disp.point(millis() / 500 % 2);
    FastLED.show();
  }
}
