#pragma once

#include <EEPROM.h>
#include "Config.h"

class Storage {
public:
    static void init();
    static void saveCalibration(float value);
    static void saveWeight(float weight);
    static void saveStandby(int minutes);
    static float loadCalibration();
    static float loadWeight();
    static int loadStandby();
    
private:
    static void commitChanges();
};