#ifndef AWSIOT_H
#define AWSIOT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class AwsIot {
public:
  AwsIot(WiFiClientSecure& net, const char* thingName, const char* awsCertCa, const char* awsCertCrt, const char* awsCertPrivate, const char* awsIotEndpoint);
  void connectToMqtt();
  void mqttLoop();
  void setCallback(MQTT_CALLBACK_SIGNATURE);
  void subscribe(const char* topic);
  void publish(const char* topic, const JsonObject& payload);
  void publishDHTData(const char* topic, float h, float t);
private:
  PubSubClient _client;
  const char* _thingName;
};

#endif // AWSIOT_H
