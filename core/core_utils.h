struct Time
{
  byte hour;
  byte minute;
  byte second;
  int ms;
};

#if DEBUG
#define logln(x) Serial.println(x)
#define log(x) Serial.print(x)
#else
#define logln(x)
#define log(x)
#endif

#define ALL(index) for(byte index = 0; index < NUM_LEDS; index++)
