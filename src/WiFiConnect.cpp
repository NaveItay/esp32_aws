#include "WiFiConnect.h"

const char* _ssid;
const char* _password;

WiFiConnect::WiFiConnect() {}

bool WiFiConnect::loadCredentials(const char* filename) {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
    return false;
  }
  
  File file = SPIFFS.open(filename);
  
  if (!file) {
    Serial.println("Failed to open file for reading");
    return false;
  }

  // Read and print the file content
  while(file.available()) {
    Serial.write(file.read());
  }

  // Rewind the file pointer to the beginning
  file.seek(0);

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println(error.c_str());
    Serial.println("Failed to read file, using default configuration");
    return false;
  }

  _ssid = doc["ssid"].as<String>();
  _password = doc["password"].as<String>();
  return true;
}


void WiFiConnect::connect() {
  Serial.print("Connecting to ");
  Serial.println(_ssid.c_str());

  WiFi.begin(_ssid.c_str(), _password.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
}


void WiFiConnect::printWiFiStatus() {
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
