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
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(this->ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
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