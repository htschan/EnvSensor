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

void WiFiHandler::connect(int timeoutSec)
{
    this->timeoutSec = timeoutSec;
    WiFi.mode(WIFI_STA);
    uint8_t mac[6];
    WiFi.macAddress(mac);
    // WiFi.setHostname("ESP32-" + String(mac[3], HEX) + String(mac[4], HEX) + String(mac[5], HEX));
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
        Serial.printf("MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
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