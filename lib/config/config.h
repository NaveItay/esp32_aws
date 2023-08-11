#pragma once    //  is a non-standard but widely supported preprocessor directive designed to cause the current source file to be included only once in a single compilation.

// AWS IoT
#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC1 "esp32/valve1"
#define AWS_IOT_SUBSCRIBE_TOPIC2 "esp32/valve2"


// DHT sensor
#define DHTPIN 27
#define IS_FAHRENHEIT false
#define DHT_INTERVAL 30000 // Reading interval (2000 ms = 2s)

// Relay
#define RELAY1 32
