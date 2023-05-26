#ifndef DHTSensor_h
#define DHTSensor_h

#include "Arduino.h"
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11

class DHTSensor {
  public:
    DHTSensor(uint8_t pin);
    bool read(float& temperature, float& humidity, bool isFahrenheit = false);
  
  private:
    uint8_t _pin;
    DHT _dht;
    float _humidity;
    float _temperature;
};

#endif
