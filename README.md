# Basic project template for ESP32 with OTA

This work is derived from https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/


# Features

- Over-the-air updates of Firmware
- Upload files for SPIFF
- Basic Authentication for OTA
- Using one asynchronous Task to monitor a digital input


# Environment

## Hostmachine

- Ubuntu 22.04.1 LTS  (jammy)
- Visual Studio Code 1.74.2 (Nov 2022)
- PlatformIO 2.5.5 (VS Code Extension)

## Target 

- CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32dev.html
- PLATFORM: Espressif 32 (5.3.0) > Espressif ESP32 Dev Module
- HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash

# Private Data

There should be a file `private_data.h` be placed in the `inlcude` folder cotaining your private credentials:

```

const char *OTAUSER = "the OTA user";
const char *OTAPASSWORD = "the OTA password";

// WiFi Server stuff and WiFi logon Credentials
const char *SSID = "the WIFI SSID";
const char *PASSWORD = "the WIFI password";

```