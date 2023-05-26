#include "DHTSensor.h"

DHTSensor::DHTSensor(uint8_t pin)
: _pin(pin), _dht(_pin, DHTTYPE) {
    _humidity = 0.0;
    _temperature = 0.0;
    _dht.begin();
}

bool DHTSensor::read(float& temperature, float& humidity, bool isFahrenheit) {
    _temperature = _dht.readTemperature(isFahrenheit);
    _humidity = _dht.readHumidity();

    temperature = _temperature;
    humidity = _humidity;
    
    // Assuming the read was successful. You should add error checking here.
    return true; 
}
