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
    void setTimeOffset(int _offset);
  private:
    WiFiUDP _UDP;
    NTPClient _timeClient;
    int _timeOffset;
};

Wifi::Wifi():
  _timeClient(_UDP)
{
  _timeClient.begin();
}

Time Wifi::getTime() {
  _timeClient.update();
  
  Time t;
  t.hour = _timeClient.getHours();
  t.minute = _timeClient.getMinutes();
  t.second = _timeClient.getSeconds();
  t.ms = 0;
  return t;
}

void Wifi::setTimeOffset(int _offset){
  _timeOffset = _offset*3600;
  _timeClient.setTimeOffset(_timeOffset);
}
