#include "Storage.h"

void Storage::init() {
    EEPROM.begin(EEPROM_SIZE);
}

void Storage::saveCalibration(float value) {
    EEPROM.writeFloat(ADDR_CALIBRATION, value);
    EEPROM.commit();
}

void Storage::saveStandby(int minutes) {
    EEPROM.writeInt(ADDR_STANDBY, minutes);
    EEPROM.commit();
}

float Storage::loadCalibration() {
    return  EEPROM.readFloat(ADDR_CALIBRATION);
}

int Storage::loadStandby() {
    int minutes = EEPROM.readInt(ADDR_STANDBY);
    if(minutes <=0 || minutes > 100) minutes = 2;
    return minutes;
}

