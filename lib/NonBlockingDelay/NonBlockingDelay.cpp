#include "NonBlockingDelay.h"

NonBlockingDelay::NonBlockingDelay(unsigned long interval)
: _interval(interval), _previousMillis(0) {
}

void NonBlockingDelay::reset() {
    _previousMillis = millis();
}

bool NonBlockingDelay::check() {
    unsigned long currentMillis = millis();
    if(currentMillis - _previousMillis >= _interval) {
        _previousMillis = currentMillis;
        return true;
    } else {
        return false;
    }
}
