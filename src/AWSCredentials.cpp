#include "AWSCredentials.h"

void loadAWSCredentials(AwsCredentials &credentials, const char *filename) {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }

  File file = SPIFFS.open(filename);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  DynamicJsonDocument doc(2048);
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("Failed to parse file");
    return;
  }

  credentials.thingName = (const char*) doc["THINGNAME"];
  credentials.awsIotEndpoint = (const char*) doc["AWS_IOT_ENDPOINT"];
  credentials.rootCA = (const char*) doc["AWS_CERT_RootCA"];
  credentials.deviceCert = (const char*) doc["AWS_CERT_DeviceCRT"];
  credentials.privateKey = (const char*) doc["AWS_CERT_PRIVATE"];

  file.close();
}
