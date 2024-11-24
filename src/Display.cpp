#include "Display.h"
#include "Logo.h"

Display::Display() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void Display::init() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
}

void Display::showWeight(float weight) {
    int weightAsInt = int(weight + 0.5);
    char weightAsString[6] = {0};
    dtostrf(weightAsInt, 5, 0, weightAsString);
    display.clearDisplay();
    display.setTextSize(4);
    display.setCursor(0, 4);
    display.println(weightAsString);
    display.display();
}

void Display::showMessage(const char* message) {
    display.clearDisplay();
    display.setCursor(0, 4);
    display.setTextSize(3);
    display.println(message);
    display.display();
}

void Display::showTare() {
    unsigned long currentTime = millis();
    char blinkChar[6] = {0};
    dtostrf(0, 5, 0, blinkChar);
    // Blink alle 500ms
    if (currentTime - lastBlinkTime >= 500) {
        lastBlinkTime = currentTime;
        blinkState = !blinkState;
        
        display.clearDisplay();
        if (blinkState) {
            display.setCursor(0, 4);
            display.println(blinkChar);
        }
        display.display();
    }
}

void Display::showLogo() {
    display.clearDisplay();
    display.drawBitmap(0, 0, pauna_esp_small_logo, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
    display.display();
}

void Display::turnOff() {
    display.ssd1306_command(SSD1306_DISPLAYOFF);
}

void Display::turnOn() {
    display.ssd1306_command(SSD1306_DISPLAYON);
}
