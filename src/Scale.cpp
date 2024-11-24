#include "Scale.h"

Scale::Scale() : loadCell(HX711_DOUT, HX711_SCK) {}

void Scale::init() {
    loadCell.begin();
    loadCell.start(600); // code adds 400ms so this is 1s init, maybe more init time?
}

void Scale::tare() {
    loadCell.tareNoDelay();
}

bool Scale::update() {
    return loadCell.update();
}

float Scale::getData() {
    return loadCell.getData();
}

void Scale::setCalibration(float value) {
    loadCell.setCalFactor(value);
}

float Scale::getNewCalibration(float knownWeight) {
    return loadCell.getNewCalibration(knownWeight);
}

void Scale::powerDown() {
    loadCell.powerDown();
}

void Scale::powerUp() {
    loadCell.powerUp();
}

bool Scale::getTareStatus() {
    return loadCell.getTareStatus();
}

void Scale::refreshDataSet() {
    loadCell.refreshDataSet();
}