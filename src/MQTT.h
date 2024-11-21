#include <Arduino.h>
#include <Wire.h>
#include <PubSubClient.h>

#include "definitions.h"

const char *pubSubId = myPUBSUBID;
const char *topic = myTOPIC;

WiFiClient espClient;
PubSubClient client(espClient);

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
  while ((millis() - connectEntry < 5000) || !client.connect(pubSubId, MQTT_USERNAME, MQTT_PASSWORD))
  {
    sleep_ms(500);
  }
  if (client.connect(pubSubId, MQTT_USERNAME, MQTT_PASSWORD))
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

void transmitData(int id, float temperature, float humidity)
{
  unsigned long entry = millis();
  char msg[200];
  JsonDocument doc;
  String jsonMessageString;

  digitalWrite(LED_ONLINE, HIGH);

  if (!client.connected())
  {
    reconnect(id);
  }
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
  serializeJson(doc, jsonMessageString);
  client.publish(topic, jsonMessageString.c_str());
  sleep_ms(1000);
  Serial.printf("Transmission time duration: %lu ms\n", millis() - entry);
  digitalWrite(LED_ONLINE, LOW);
}
