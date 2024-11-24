// include/Config.h
#pragma once

#include <Arduino.h>

// Display definitions
#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Pin definitions
#define BUTTON_PIN 3
#define HX711_DOUT 8
#define HX711_SCK 20

// Network settings
#define DNS_PORT 53
#define EEPROM_SIZE 512

// EEPROM address definitions
#define ADDR_CALIBRATION 0
#define ADDR_STANDBY 16
