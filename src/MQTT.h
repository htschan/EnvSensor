#include <Arduino.h>
#include <Wire.h>
#include <PubSubClient.h>

#include "definitions.h"

const char *pubSubId = myPUBSUBID;
const char *topic = myTOPIC;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect(int id)
{
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  Serial.print("Attempting MQTT connection...");
  unsigned long connectEntry = millis();
  while ((millis() - connectEntry < 5000) && !client.connected())
  {
    client.connect(pubSubId, MQTT_USERNAME, MQTT_PASSWORD);
    sleep_ms(500);
  }
  if (client.connected())
  {
    JsonDocument doc;
    String jsonMessageString;

    doc["CONNECTION"] = "MQTT Connected";
    doc["I"] = id;
    serializeJson(doc, jsonMessageString);
    Serial.println("MQTT Connected");
    // Once connected, publish an announcement...
    client.publish(myTOPICSTATUS, jsonMessageString.c_str());
    // ... and resubscribe
    client.subscribe("inTopic");
  }
  else
  {
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println(" try again in 5 seconds");
    // Wait 5 seconds before retrying
    //      NVIC_SystemReset();
  }
}

void transmitData(int id, float temperature, float humidity, bool presence);

void transmitData(int id, float temperature, float humidity)
{
  transmitData(id, temperature, humidity, false);
}

void transmitData(int id, float temperature, float humidity, bool presence)
{
  unsigned long entry = millis();
  JsonDocument doc;
  String jsonMessageString;

  digitalWrite(LED_ONLINE, HIGH);

  if (!client.connected())
  {
    reconnect(id);
  }
  client.loop();
#ifdef DEBUG
  Serial.println(F("Transmitting packet ... "));
#endif

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  // NOTE: transmit() is a blocking method!
  //       See example SX128x_Transmit_Interrupt for details
  //       on non-blocking transmission method.

  doc["I"] = id;
  doc["T"] = temperature;
  doc["H"] = humidity;
  doc["P"] = presence;
  serializeJson(doc, jsonMessageString);
  client.publish(topic, jsonMessageString.c_str());
  Serial.printf("Transmission time duration: %lu ms\n", millis() - entry);
  digitalWrite(LED_ONLINE, LOW);
}
