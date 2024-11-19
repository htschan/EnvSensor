#ifndef DHT11HANDLER_H
#define DHT11HANDLER_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>

#include "definitions.h"

class DHT11Handler
{
public:
    DHT11Handler(int pin);
    void begin();
    float readTemperature();
    float readHumidity();
    uint32_t delayMS;

private:
    int _pin;
    float _temperature;
    float _humidity;
    DHT_Unified *pdht;
};

#endif // DHT11HANDLER_H