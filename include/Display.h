#pragma once

#include <Adafruit_SSD1306.h>
#include "Config.h"

class Display {
public:
    Display();
    void init();
    void showWeight(float weight);
    void showMessage(const char* message);
    void showLogo();
    void showTare();
    void turnOff();
    void turnOn();
    
private:
    Adafruit_SSD1306 display;
    unsigned long lastBlinkTime;
    bool blinkState;
};