#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WAKEUP_SWITCH 9
#define LED_ONLINE 10
#define DHTPIN 22           // Digital pin connected to the DHT sensor (use 4.7 kOhm pull-up resistor)
#define DHTTYPE DHT22       // DHT 22 (AM2302)
#define WLAN_ON_INTERVAL (3 * 60 * 1000) // 3 minutes
//#define DATA_TRANSMIT_INTERVAL (5 * 60 * 1000) // 5 minutes
#define DATA_TRANSMIT_INTERVAL (1 * 60 * 1000) // 5 minutes

#define myTOPICSTATUS "/EnviroMonitorStatus"

// override above mentioned private data
#include "private_data.h"

#endif // DEFINITIONS_H