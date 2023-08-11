// AWSCredentials.h

#ifndef AWSCREDENTIALS_H
#define AWSCREDENTIALS_H

#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

struct AwsCredentials {
  String thingName;
  String awsIotEndpoint;
  String rootCA;
  String deviceCert;
  String privateKey;
};

void loadAWSCredentials(AwsCredentials &credentials, const char *filename);

#endif
