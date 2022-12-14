/*
   l9_light_alpha
   by far-galaxy
*/

#define DEBUG 1

#include "core_utils.h"
#include "led_utils.h"
#include "wifi_utils.h"
#include "buildTime.h"
#include <GyverTM1637.h>

#include "connection.h"

GyverTM1637 disp(D1, D2);

Time t;
LED led;
Wifi wifi;

void setup() {
#if DEBUG
  Serial.begin(115200);
#endif

  disp.clear();
  disp.brightness(7);

  wifi.scan();

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED )
  {
    delay ( 500 );
    log ( "." );
  }
  logln( "!!!" );

  wifi.setTimeOffset(3);
  t = wifi.getTime();
  led.fill(CRGB::Black);
  led.show();
  led.fill(CRGB::Red);
}

void loop() {
  static long timer = 0;
  static long tick = 0;

  unsigned long now = millis();

  if (now - tick >= 5){
    led.tick();
  }

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
  }
}
