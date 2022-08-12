#if DEBUG
#define logln(x) Serial.println(x)
#define log(x) Serial.print(x)
#else
#define logln(x)
#define log(x)
#endif
