#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define WAKEUP_SWITCH 9
#define LED_ONLINE 10       // LED that stays on when the device is online and connected to Wi-Fi (red)
#define LED_PRESENCE 11     // LED that flashes when presence is detected (green)
#define DHTPIN 22           // Digital pin connected to the DHT sensor (use 4.7 kOhm pull-up resistor)
#define DHTTYPE DHT22       // DHT 22 (AM2302)
#define LD2410_UART_TX_PIN 12
#define LD2410_UART_RX_PIN 13
#define LD2410_OUT_PIN 14
#define LD2410_UART_BAUD 256000
#define PRESENCE_POLL_INTERVAL_MS 100
#define PRESENCE_DEBOUNCE_MS 500
#define PRESENCE_LED_FLASH_DURATION_MS 1000  // How long the LED stays on when presence detected
#define WLAN_ON_INTERVAL (3 * 60 * 1000) // 3 minutes
//#define DATA_TRANSMIT_INTERVAL (5 * 60 * 1000) // 5 minutes
#define DATA_TRANSMIT_INTERVAL (1 * 60 * 1000) // 1 minutes

#define myTOPICSTATUS "/EnviroMonitorStatus"

// override above mentioned private data
#include "private_data.h"

#endif // DEFINITIONS_H