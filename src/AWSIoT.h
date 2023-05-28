#ifndef AWSIOT_H
#define AWSIOT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class AwsIot {
public:
  AwsIot(WiFiClientSecure& net, const char* thingName, const char* awsCertCa, const char* awsCertCrt, const char* awsCertPrivate, const char* awsIotEndpoint);
  void connectToMqtt();
  void mqttLoop();
  void setCallback(MQTT_CALLBACK_SIGNATURE);
  void subscribe(const char* topic);
private:
  PubSubClient _client;
  const char* _thingName;  // add this line
};

#endif // AWSIOT_H