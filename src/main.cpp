#include "DHTSensor.h"
#include "NonBlockingDelay.h"
#include "WiFiConnect.h"
#include "config.h"

// AWS IoT
#include <WiFiClientSecure.h>
#include "AWSIoT.h"
#include "aws_secrets.h"

// Init WiFi
WiFiConnect wifi;

// Init AWS IoT
WiFiClientSecure net = WiFiClientSecure();
AwsIot awsIot(net, THINGNAME, AWS_CERT_RootCA, AWS_CERT_DeviceCRT, AWS_CERT_PRIVATE, AWS_IOT_ENDPOINT);

// Init DHT sensor
DHTSensor dht(DHTPIN);

// Init NonBlockingDelay
NonBlockingDelay dht_timer(DHT_INTERVAL);

// function declarations
void MQTTmessageHandler(char *topic, byte *payload, unsigned int length);

void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);

  // reset timers
  dht_timer.reset();

  // Load WiFi credentials from flash memory using SPIFFS, connect to WiFi, and print connection status. 
  if (!wifi.loadCredentials("/wifi_config.json")) {
    Serial.println("Failed to load Wi-Fi credentials");
    return;
  }
  wifi.connect();
  wifi.printWiFiStatus();

  // AWS IoT
  awsIot.setCallback(MQTTmessageHandler);
  awsIot.connectToMqtt();
  awsIot.subscribe(AWS_IOT_SUBSCRIBE_TOPIC1);
}

void loop() {
  if (dht_timer.check()) {
    float temperature = 0;
    float humidity = 0;

    if (dht.read(temperature, humidity, IS_FAHRENHEIT)) {
      // char temp_unit = IS_FAHRENHEIT ? 'F' : 'C';
      // Serial.printf("Humidity: %.2f %%  Temperature: %.2f %c\n", humidity, temperature, temp_unit);

      // publish to AWS IoT Core using MQTT Protocol
      awsIot.publishDHTData(AWS_IOT_PUBLISH_TOPIC, humidity, temperature);  
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }

  awsIot.mqttLoop();
}

void MQTTmessageHandler(char* topic, byte* payload, unsigned int length)
{
  // We need to ensure the payload is null-terminated for printf to work correctly.
  // First, we need to create a new buffer of length + 1, then copy the payload into it, and finally, null-terminate it.
  char* nullTerminatedPayload = new char[length + 1];
  memcpy(nullTerminatedPayload, payload, length);
  nullTerminatedPayload[length] = '\0';

  // Now we can safely print the null-terminated payload with printf.
  // Note: %s expects a null-terminated string.
  Serial.printf("Incoming: topic=%s, payload=%s, length=%u\n", topic, nullTerminatedPayload, length);
  
  // Don't forget to delete the buffer when you're done to avoid a memory leak.
  delete[] nullTerminatedPayload;
 
  /*##################### Valve 1 #####################*/
  if ( strstr(topic, "esp32/valve1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    int r1 = doc["status"].as<int>(); // directly convert to integer

    digitalWrite(RELAY1, r1 == 1 ? LOW : HIGH);
    Serial.println(r1 == 1 ? "Valve1 is ON" : "Valve1 is OFF");
  }
}
