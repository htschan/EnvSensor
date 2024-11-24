#include <Arduino.h>

#include "wifiHandler.h"
#include "definitions.h"

WiFiHandler::WiFiHandler(const char *ssid, const char *password)
{
    this->ssid = ssid;
    this->password = password;
    this->wlanConnected = false;
    this->lastWlanConnected = millis();
    pinMode(LED_ONLINE, OUTPUT); // Show online status
}

DeviceInfo devices[] = {
    {{0x28, 0xCD, 0xC1, 0x0B, 0x1B, 0xC8}, 1, "THSens-1"},
    {{0x28, 0xCD, 0xC1, 0x02, 0xA3, 0xAA}, 2, "THSens-2"},
    {{0x28, 0xCD, 0xC1, 0x02, 0x97, 0x26}, 3, "THSens-3"},
    {{0x28, 0xCD, 0xC1, 0x02, 0x87, 0xB4}, 4, "THSens-4"}};

bool WiFiHandler::getDeviceInfoByMAC(const uint8_t *mac, int &id, const char *&hostname)
{
    for (const auto &device : devices)
    {
        if (memcmp(device.mac, mac, 6) == 0)
        {
            id = device.id;
            hostname = device.hostname;
            return true;
        }
    }
    return false;
}

void WiFiHandler::connect(int timeoutSec)
{
    this->timeoutSec = timeoutSec;
    WiFi.mode(WIFI_STA);
    uint8_t mac[6];
    WiFi.macAddress(mac);
    getDeviceInfoByMAC(mac, hostId, hostName);
    WiFi.setHostname(hostName);

    WiFi.begin(this->ssid, this->password);
    unsigned long entry = millis();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (timeoutSec != 0 && (millis() - entry) > (timeoutSec * 1000))
        {
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.printf("Connected to %s\nIP address: %s\n", this->ssid, WiFi.localIP().toString().c_str());
        Serial.printf("MAC address: %02X:%02X:%02X:%02X:%02X:%02X  Hostname: %s\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], hostName);
        digitalWrite(LED_ONLINE, HIGH);
        wlanConnected = true;
        lastWlanConnected = millis();
    }
}

void WiFiHandler::handleTimeout()
{
    if (millis() - lastWlanConnected > this->timeoutSec * 1000 && wlanConnected)
    {
        this->disconnect();
    }
}

void WiFiHandler::disconnect()
{
    wlanConnected = false;
    WiFi.disconnect();
    delay(100);
    Serial.println("Disconnected from WiFi");
    digitalWrite(LED_ONLINE, LOW);
}

bool WiFiHandler::isConnected()
{
    return wlanConnected;
}