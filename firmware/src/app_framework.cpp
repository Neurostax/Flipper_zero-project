#include "app_framework.h"
#include "ui_display.h"
#include "gpio_control.h"
#include <Arduino.h>

extern UIDisplay display;
extern GPIOControl gpio;

void MainMenuApp::start() {
    selectedIndex = 0;
    lastButtonPress = millis();
}

void MainMenuApp::tick() {
    unsigned long currentTime = millis();

    // 1. Process Input (With simple debouncing)
    if (currentTime - lastButtonPress > DEBOUNCE_DELAY) {
        if (gpio.isUpPressed()) {
            selectedIndex--;
            if (selectedIndex < 0) selectedIndex = NUM_ITEMS - 1;
            lastButtonPress = currentTime;
        } 
        else if (gpio.isDownPressed()) {
            selectedIndex++;
            if (selectedIndex >= NUM_ITEMS) selectedIndex = 0;
            lastButtonPress = currentTime;
        } 
        else if (gpio.isSelectPressed()) {
            // Future: Launch selected app plugin
            // activeApp = new NFCApp(); 
            // activeApp->start();
            lastButtonPress = currentTime;
        }
    }

    // 2. Render UI Display
    display.clear();
    
    // Header
    display.drawRectangle(0, 0, 128, 12);
    display.drawText(18, 2, "FLIPPER MENU");

    // Scrollable List
    for (int i = 0; i < NUM_ITEMS; i++) {
        int y_pos = 16 + (i * 12); // Layout spacing
        if (i == selectedIndex) {
            display.drawText(0, y_pos, "> " + menuItems[i]); // Cursor
        } else {
            display.drawText(12, y_pos, menuItems[i]);
        }
    }
}

void MainMenuApp::stop() {
    display.clear();
}