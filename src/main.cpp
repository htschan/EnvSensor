#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ElegantOTA.h>
#include "MQTT.h"

#include "switchDebouncer.h"
#include "wifiHandler.h"
#include "dht11Handler.h"

#include "definitions.h"

WebServer server(80);
unsigned long ota_progress_millis = 0;
unsigned long lastTransmitData = millis();
unsigned long lastMeasurement = millis();

float t = 0.0;
float h = 0.0;

SwitchDebouncer onlineSwitchDebouncer(WAKEUP_SWITCH, 5000);
WiFiHandler wifiHandler(SSID, PASS);
DHT11Handler dht11(DHTPIN);

void onOTAStart()
{
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void onOTAProgress(size_t current, size_t final)
{
  // Log every 1 second
  if (millis() - ota_progress_millis > 1000)
  {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void onOTAEnd(bool success)
{
  // Log when OTA has finished
  if (success)
  {
    Serial.println("OTA update finished successfully!");
  }
  else
  {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}

void setup()
{
  // initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT); // Serial port for debugging purposes
  pinMode(LED_ONLINE, OUTPUT);  // Show online status

  digitalWrite(LED_ONLINE, HIGH);

  Serial.begin(115200);

  server.on("/", []()
            { server.send(200, "text/html", "<!DOCTYPE html><html><body><h1>Hi! This is the Temperature and Humidity sensor.</h1></body></html>"); });

  ElegantOTA.begin(&server); // Start ElegantOTA
  ElegantOTA.setAutoReboot(true);
  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.begin();
  Serial.println("HTTP server started");

  dht11.begin();
  Serial.println("Ready");
  sleep_ms(500);
  digitalWrite(LED_ONLINE, LOW);
  sleep_ms(500);
  digitalWrite(LED_ONLINE, HIGH);
  sleep_ms(1000);
  digitalWrite(LED_ONLINE, LOW);
}

void loop()
{
  server.handleClient();
  ElegantOTA.loop();
  // wifiHandler.handleTimeout();
  onlineSwitchDebouncer.read();
  // if (onlineSwitchDebouncer.isPressed())
  // {
  //   if (!wifiHandler.isConnected())
  //   {
  //     Serial.println("--- Switch pressed and WLAN not connected ---");
  //     wifiHandler.connect(WLAN_ON_INTERVAL);
  //   }
  // }

  if (millis() - lastMeasurement > dht11.delayMS * 10)
  {
    lastMeasurement = millis();
    t = dht11.readTemperature();
    h = dht11.readHumidity();
  }
  if (millis() - lastTransmitData > DATA_TRANSMIT_INTERVAL)
  {
    bool doDisconnect = false;
    Serial.println("Transmitting data ...");
    if (!wifiHandler.isConnected())
    {
      wifiHandler.connect(0);
      doDisconnect = true;
    }
    lastTransmitData = millis();
    transmitData(1, t, h);
    // if (doDisconnect)
    // {
    //   Serial.println("Disconnecting ...");
    //   wifiHandler.disconnect();
    // }
  }
}
