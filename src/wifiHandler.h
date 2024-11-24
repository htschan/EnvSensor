#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>

struct DeviceInfo {
  uint8_t mac[6];
  int id;
  const char* hostname;
};

class WiFiHandler
{
public:
    WiFiHandler(const char *ssid, const char *password);
    void connect(int timeoutSec); // 0 = no limit
    void handleTimeout();
    void disconnect();
    bool isConnected();
    int hostId;
    const char *hostName;

private:
    bool getDeviceInfoByMAC(const uint8_t* mac, int &hostId, const char* &hostName);
    const char *ssid;
    const char *password;

    bool wlanConnected;

    unsigned long lastWlanConnected;
    int timeoutSec;
};

#endif // WIFIHANDLER_H