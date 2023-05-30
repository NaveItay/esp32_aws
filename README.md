# ESP32 AWS IoT Core Project
![AWS IoT Core Diagram]("what-is-aws-iot.jpg")

This project aims to connect an ESP32 to AWS IoT Core using MQTT to send sensor readings from a DHT sensor and control a relay module.

## Features
* Connects to WiFi using credentials stored in SPIFFS.
* Reads temperature and humidity data from a DHT sensor.
* Publishes DHT sensor readings to AWS IoT Core using MQTT.
* Subscribes to a topic to receive commands from AWS IoT Core to control a relay module.
* Uses non-blocking delay to manage the reading intervals of the DHT sensor.

## Hardware
* Adafruit Feather ESP32
* DHT sensor
* Relay module

## Software
* PlatformIO

## License
* This project is licensed under the MIT License
