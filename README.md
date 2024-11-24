# Environment sensor using Raspberry Pi Pico W - RP2040

This work is derived from https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/


# Features

- Over-the-air updates of Firmware
- Upload files for SPIFF
- Basic Authentication for OTA
- Using one asynchronous Task to monitor a digital input


# Environment

## Hostmachine

- Ubuntu 22.04.1 LTS  (jammy)
- Visual Studio Code 1.95.2 (Nov 2024)
- PlatformIO 3.4.4 (VS Code Extension)

## Target 

- CONFIGURATION: https://docs.platformio.org/en/latest/boards/raspberrypi/pico.html?utm_source=platformio&utm_medium=piohome#frameworks
- PLATFORM: Raspberry Pi Pico
- HARDWARE: Pico W 2040

# Private Data

There should be a file `private_data.h` be placed in the `inlcude` folder cotaining your private credentials:

```

const char *OTAUSER = "the OTA user";
const char *OTAPASSWORD = "the OTA password";

// WiFi Server stuff and WiFi logon Credentials
const char *SSID = "the WIFI SSID";
const char *PASSWORD = "the WIFI password";

#define myPUBSUBID "xxxxx"
#define myTOPIC "/xxxxx"

#define MQTT_PORT nnn
#define MQTT_SERVER "o.p.q.r"
#define MQTT_USERNAME "xxxx"
#define MQTT_PASSWORD "xxxxx"

```