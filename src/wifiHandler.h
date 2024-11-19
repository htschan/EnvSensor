#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>

class WiFiHandler
{
public:
    WiFiHandler(const char *ssid, const char *password);
    void connect(int timeoutSec); // 0 = no limit
    void handleTimeout();
    void disconnect();
    bool isConnected();

private:
    const char *ssid;
    const char *password;

    bool wlanConnected;

    unsigned long lastWlanConnected;
    int timeoutSec;
};

#endif // WIFIHANDLER_H