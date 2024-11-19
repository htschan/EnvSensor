#include <Arduino.h>
#include "switchDebouncer.h"
#include "definitions.h"

SwitchDebouncer::SwitchDebouncer(int pin, int debounceDelayMsec)
{
    this->pin = pin;
    this->debounceDelay = debounceDelayMsec;
    this->lastDebounceTime = 0;
    this->lastButtonState = HIGH;
    this->buttonState = HIGH;
    pinMode(WAKEUP_SWITCH, INPUT_PULLUP);
}

void SwitchDebouncer::read()
{
    int reading = digitalRead(pin);

    if (reading != lastButtonState)
    {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        if (reading != buttonState)
        {
            buttonState = reading;
        }
    }

    lastButtonState = reading;
}

bool SwitchDebouncer::isPressed()
{
    return buttonState == LOW;
}