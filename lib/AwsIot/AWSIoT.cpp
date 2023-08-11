#include "AWSIoT.h"
#include <Arduino.h>

AwsIot::AwsIot(WiFiClientSecure& net, const char* thingName, const char* awsCertCa, const char* awsCertCrt, const char* awsCertPrivate, const char* awsIotEndpoint)
  : _client(net), _thingName(thingName)
{
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(awsCertCa);
  net.setCertificate(awsCertCrt);
  net.setPrivateKey(awsCertPrivate);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  _client.setServer(awsIotEndpoint, 8883);
}

void AwsIot::connectToMqtt() {
  Serial.println("Connecting to AWS IOT");

  while (!_client.connect(_thingName)) {
    Serial.print(".");
    delay(100);
  }

  if (!_client.connected()) {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  Serial.println("AWS IoT Connected!");
}

void AwsIot::mqttLoop() {
  _client.loop();
}

void AwsIot::setCallback(MQTT_CALLBACK_SIGNATURE) {
  _client.setCallback(callback);
}

void AwsIot::subscribe(const char* topic) {
  _client.subscribe(topic);
}

void AwsIot::publish(const char* topic, const JsonObject& payload) {
  char buffer[512];  // Buffer size depends on your payload
  serializeJson(payload, buffer);
  
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print(" Payload: ");
  Serial.println(buffer); // Buffer now contains the serialized JSON payload
  
  _client.publish(topic, buffer);
}

void AwsIot::publishDHTData(const char* topic, float h, float t) {
  StaticJsonDocument<200> doc;
  doc["humidity"] = h;
  doc["temperature"] = t;
  
  JsonObject obj = doc.as<JsonObject>();  // Convert StaticJsonDocument to JsonObject
  
  this->publish(topic, obj); 
}

