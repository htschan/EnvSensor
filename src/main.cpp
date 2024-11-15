#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
// #include <WebServer.h>
#include <ElegantOTA.h>
#include "MQTT.h"

// override above mentioned private data
#include "private_data.h"

WebServer server(80);
int doorState = 0;
unsigned long ota_progress_millis = 0;
unsigned long lastTimestamp = millis();
unsigned long ledToggle = millis();

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

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  
  server.on("/", []()
            { server.send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo."); });

  ElegantOTA.begin(&server); // Start ElegantOTA
  ElegantOTA.setAutoReboot(true);
  // ElegantOTA callbacks
  ElegantOTA.onStart(onOTAStart);
  ElegantOTA.onProgress(onOTAProgress);
  ElegantOTA.onEnd(onOTAEnd);

  server.begin();
  Serial.println("HTTP server started");

  Serial.println("Ready");
}

void loop()
{
  server.handleClient();
  ElegantOTA.loop();
  if (millis() - ledToggle > 1000)
  {
    ledToggle = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  if (millis() - lastTimestamp > 10000)
  {
    lastTimestamp = millis();
    transmitData(doorState);
    doorState = doorState == 0 ? 1 : 0;
  }
}
