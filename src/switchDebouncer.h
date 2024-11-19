#ifndef SWITCH_DEBOUNCER_H
#define SWITCH_DEBOUNCER_H

#define LOW 0
#define HIGH 1

class SwitchDebouncer
{
public:
    SwitchDebouncer(int pin, int debounceDelayMsec);
    void read();
    bool isPressed();

private:
    int pin;
    int debounceDelay;
    unsigned long lastDebounceTime;
    int lastButtonState;
    int buttonState;
};

#endif // SWITCH_DEBOUNCER_H