#ifndef NonBlockingDelay_h
#define NonBlockingDelay_h

#include "Arduino.h"

class NonBlockingDelay {
  public:
    NonBlockingDelay(unsigned long interval);
    void reset();
    bool check();
  
  private:
    unsigned long _interval;
    unsigned long _previousMillis;
};

#endif
