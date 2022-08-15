#pragma once
#include <Arduino.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class Wifi
{
  public:
    Wifi();
    Time getTime();
    void scan();
    void setTimeOffset(int _offset);
  private:
    WiFiUDP _UDP;
    NTPClient _timeClient;
    int _timeOffset;
    String _nets;
};

Wifi::Wifi():
  _timeClient(_UDP)
{
  _timeClient.begin();
}

Time Wifi::getTime()
{
  _timeClient.update();

  Time t;
  t.hour = _timeClient.getHours();
  t.minute = _timeClient.getMinutes();
  t.second = _timeClient.getSeconds();
  t.ms = 0;
  return t;
}

void Wifi::scan()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  logln(F("Starting WiFi scan..."));

  int scanResult;
  _nets = "";

  scanResult = WiFi.scanNetworks(false, false);
  logln("Nets finded: " + String(scanResult));

  if (scanResult > 0) {
    for (int8_t i = 0; i < scanResult; i++) {
      _nets += (String) "<div class='net" + (WiFi.encryptionType(i) == ENC_TYPE_NONE ? " open" : "") + "' onclick='pass(this)'>" + WiFi.SSID(i) + "</div>\n";
      Serial.println(WiFi.SSID(i));
      delay(0);
    }
  }

  else {
    _nets = "<div>No networks found!</div>\n";
    logln(F("No networks found!"));
  }
}

void Wifi::setTimeOffset(int _offset) {
  _timeOffset = _offset * 3600;
  _timeClient.setTimeOffset(_timeOffset);
}
