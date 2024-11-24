#pragma once

#include <HX711_ADC.h>
#include "Config.h"

class Scale {
public:
    Scale();
    void init();
    void tare();
    bool update();
    float getData();
    void setCalibration(float value);
    float getNewCalibration(float knownWeight);
    void powerDown();
    void powerUp();
    bool getTareStatus();
    void refreshDataSet();
    
private:
    HX711_ADC loadCell;
};
