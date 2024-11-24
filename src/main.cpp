#include <Arduino.h>
#include "Display.h"
#include "Scale.h"
#include "Storage.h"
#include "WebConfig.h"

Display display;
Scale scale;
WebConfig webConfig;

bool settingMode = false;
unsigned long tLastChange = 0;
unsigned long t = 0;
float weight = 0.0;
float lastWeight = 9999.0;
int standbyMS = 0.0;

void handleTare();
void handleSleep();

void setup() {
    pinMode(BUTTON_PIN, INPUT);
    
    Storage::init();
    display.init();
    display.showLogo();
    scale.init();
    
    standbyMS = Storage::loadStandby() * 60000.0;
    float calibrationValue = Storage::loadCalibration();
    if (!isfinite(calibrationValue) || calibrationValue <= 0.000001f) {
        scale.setCalibration(500); // this improves the wrong reading to be not absolutly bogus
        settingMode = true;
        webConfig.init();
    } else {
        Serial.print("cal ");
        Serial.println(calibrationValue);
        scale.setCalibration(calibrationValue);
    }
}

void loop() {
    if (settingMode) {
        display.showMessage("Setting");
        webConfig.handleClient();
        return;
    }
    
    if (digitalRead(BUTTON_PIN) == HIGH) {
        handleTare();
    }
    
    static boolean newDataReady = 0;
    if (scale.update()) newDataReady = true;
    
    if (newDataReady) {
        if (millis() > t + 25) {
            weight = scale.getData();
            display.showWeight(weight);
            if (abs(weight - lastWeight) >= 1) {
                tLastChange = millis();
                lastWeight = weight;
            }
            
            newDataReady = 0;
            t = millis();
        }
    }
    
    if (millis() > (tLastChange + (standbyMS))) {
        handleSleep();
    }
}

void handleTare() {
    scale.tare();
    
    while (!scale.getTareStatus()) {
        display.showTare();
        scale.update();
        delay(50);
    }
    
    if (digitalRead(BUTTON_PIN) == HIGH) {
        settingMode = true;
        webConfig.init();
    }
    
    tLastChange = millis();
}

void handleSleep() {
    scale.powerDown();
    display.turnOff();
    esp_deep_sleep_enable_gpio_wakeup(BIT(D1), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_deep_sleep_start();
    
    scale.powerUp();
    display.turnOn();
    
    display.init();
    display.showLogo();
    scale.init();
    scale.setCalibration(Storage::loadCalibration());
}
