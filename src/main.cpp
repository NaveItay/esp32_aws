#include "DHTSensor.h"
#include "NonBlockingDelay.h"
#include "WiFiConnect.h"

// AWS IoT
// #include "AWSCredentials.h"
#include <WiFiClientSecure.h>
#include "AWSIoT.h"
#include "secrets.h"

// Init WiFi
WiFiConnect wifi;

// Init AWS IoT
WiFiClientSecure net = WiFiClientSecure();
AwsIot awsIot(net, THINGNAME, AWS_CERT_RootCA, AWS_CERT_DeviceCRT, AWS_CERT_PRIVATE, AWS_IOT_ENDPOINT);
#define AWS_IOT_PUBLISH_TOPIC    "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/valve1"

// Init DHT sensor
#define DHTPIN 27
#define isFahrenheit false
#define DHT_INTERVAL 5000 // Reading interval (2000 ms = 2s)
DHTSensor dht(DHTPIN);

// Init NonBlockingDelay
NonBlockingDelay dht_timer(DHT_INTERVAL);  // 2 seconds interval


// function declarations
void MQTTmessageHandler(char *topic, byte *payload, unsigned int length);

void setup() {
  Serial.begin(115200);

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

    if (dht.read(temperature, humidity, isFahrenheit)) {
      char temp_unit = isFahrenheit ? 'F' : 'C';
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
 
/*##################### Lamp 1 #####################*/
  if ( strstr(topic, "esp32/valve1") )
  {
    StaticJsonDocument<200> doc;
    deserializeJson(doc, payload);
    String Relay1 = doc["status"];
    int r1 = Relay1.toInt();
    if(r1==1)
    {
      digitalWrite(32, LOW);
      Serial.println("Valve1 is ON");
    }
    else if(r1==0)
    {
      digitalWrite(32, HIGH);
      Serial.println("Valve1 is OFF");
    }
  }
}