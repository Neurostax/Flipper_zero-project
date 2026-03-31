#include "ui_display.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// From Hardware Pinout Map
#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

UIDisplay::UIDisplay() {
    oled = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

UIDisplay::~UIDisplay() {
    delete oled;
}

void UIDisplay::initialize() {
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    if (!oled->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        // Initialization failed
        return;
    }
    oled->clearDisplay();
    oled->setTextColor(SSD1306_WHITE);
    oled->setTextSize(1);
    oled->display();
}

void UIDisplay::clear() {
    oled->clearDisplay();
}

void UIDisplay::drawText(int x, int y, const std::string& text) {
    oled->setCursor(x, y);
    oled->print(text.c_str());
}

void UIDisplay::drawRectangle(int x, int y, int width, int height) {
    oled->drawRect(x, y, width, height, SSD1306_WHITE);
}

void UIDisplay::update() {
    oled->display();
}

void UIDisplay::showText(const std::string& message) {
    clear();
    drawText(10, 10, message);
    update();
}