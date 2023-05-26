#include "DHTSensor.h"
#include "NonBlockingDelay.h"

// Init DHT sensor
#define DHTPIN 27
#define isFahrenheit false
#define DHT_INTERVAL 2000 // Reading interval (2000 ms = 2s)
DHTSensor dht(DHTPIN);

// Init NonBlockingDelay
NonBlockingDelay dht_timer(DHT_INTERVAL);

void setup() {
  Serial.begin(115200);
  dht_timer.reset();
}

void loop() {
  if (dht_timer.check()) {
    float temperature = 0;
    float humidity = 0;

    if (dht.read(temperature, humidity, isFahrenheit)) {
      char temp_unit = isFahrenheit ? 'F' : 'C';
      Serial.printf("Humidity: %.2f %%  Temperature: %.2f %c\n", humidity, temperature, temp_unit);
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }
}
