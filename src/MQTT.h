#include <Arduino.h>
#include <Wire.h>
#include <PubSubClient.h>

#include "definitions.h"

const char *pubSubId = myPUBSUBID;
const char *topic = myTOPIC;
bool led_tick = false;

WiFiClient espClient;
PubSubClient client(espClient);

#define QUEUE_SIZE 10

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

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1')
  {
    // digitalWrite(LED_GREEN, LOW); // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  }
  else
  {
    // digitalWrite(LED_GREEN, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

void reconnect()
{
  Serial.print("Attempting MQTT connection...");
  unsigned long connectEntry = millis();
  while ((millis() - connectEntry < 5000) || !client.connect(pubSubId, MQTT_USERNAME, MQTT_PASSWORD))
  {
    sleep_ms(500);
  }
  if (client.connect(pubSubId, MQTT_USERNAME, MQTT_PASSWORD))
  {
    Serial.println("MQTT Connected");
    // Once connected, publish an announcement...
    client.publish(topic, "booted");
    // ... and resubscribe
    client.subscribe("inTopic");
  }
//   else
//   {
//     Serial.print("failed, rc=");
//     Serial.print(client.state());
//     Serial.println(" try again in 5 seconds");
//     // Wait 5 seconds before retrying
//     NVIC_SystemReset();
//   }
}

void transmitFinalData()
{
  unsigned long entry = millis();
  char msg[400];
  JsonDocument doc;
  String jsonMessageString;

  if (!client.connected())
  {
    reconnect();
  }
#ifdef DEBUG
  Serial.println(F("Transmitting packet ... "));
#endif

  doc["Sp"] = "21";
  doc["Re"] = "1111";
  doc["Du"] = "434234";

  //  for (int ii = 0; ii < 5; ii++) {
  //    if (charPropTransfer[ii] > 6900) {
  //      doc[String(ii)] = String(char(charPropTransfer[ii] % 100));   // Transfer Ranking of letters above 50 propability
  //    }
  //  }
  serializeJson(doc, jsonMessageString);
  Serial.println(msg);
  client.publish(topic, jsonMessageString.c_str());
}

void transmitData(int doorState)
{
  unsigned long entry = millis();
  char msg[200];
  JsonDocument doc;
  String jsonMessageString;

//   digitalWrite(MY_LED_BUILTIN, led_tick ? HIGH : LOW); // Turn the LED on by making the voltage HIGH
  led_tick = !led_tick;

  if (!client.connected())
  {
    reconnect();
  }
#ifdef DEBUG
  Serial.println(F("Transmitting packet ... "));
#endif

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  // NOTE: transmit() is a blocking method!
  //       See example SX128x_Transmit_Interrupt for details
  //       on non-blocking transmission method.

  doc["DoorState"] = doorState;
  serializeJson(doc, jsonMessageString);
  client.publish(topic, jsonMessageString.c_str());
  Serial.print(millis() - entry);
}
