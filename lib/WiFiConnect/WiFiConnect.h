#ifndef WiFiConnect_h
#define WiFiConnect_h

#include <WiFi.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>


class WiFiConnect {
public:
  WiFiConnect();
  bool loadCredentials(const char* filename);
  void connect();
  void printWiFiStatus();
private:
  String _ssid;
  String _password;
};


#endif