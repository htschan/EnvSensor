
#include "dht11Handler.h"

DHT11Handler::DHT11Handler(int pin)
{
    this->_pin = pin;
    this->_temperature = 0.0;
    this->_humidity = 0.0;
    this->pdht = new DHT_Unified(pin, DHTTYPE);
}

void DHT11Handler::begin()
{
    pdht->begin();

    sensor_t sensor;
    pdht->temperature().getSensor(&sensor);

    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("°C"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("°C"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
    pdht->humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Driver Ver:  "));
    Serial.println(sensor.version);
    Serial.print(F("Unique ID:   "));
    Serial.println(sensor.sensor_id);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("%"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("%"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    // Set delay between sensor readings based on sensor details.
    Serial.print(F("Min delay:  "));
    Serial.print(sensor.min_delay / 1000);
    Serial.println(F("msec"));
    delayMS = sensor.min_delay / 1000;

    Serial.println(F("------------------------------------"));
}

float DHT11Handler::readTemperature()
{
    sensors_event_t event;

    pdht->temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
        Serial.println(F("Error reading temperature!"));
        return 0.0;
    }
    else
    {
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
        return event.temperature;
    }
}

float DHT11Handler::readHumidity()
{
    sensors_event_t event;
    pdht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
        Serial.println(F("Error reading humidity!"));
        return 0.0;
    }
    else
    {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
        return event.relative_humidity;
    }
}
