#include "gpio_control.h"

// Hardware Pin Definitions from docs/21_Hardware_Pinout_Map.md
#define PIN_BTN_UP     4
#define PIN_BTN_DOWN   15
#define PIN_BTN_SELECT 18
#define PIN_BTN_BACK   19

void GPIOControl::initialize() {
    // Configure pins with internal pull-up resistors
    // Buttons should connect pin to GND when pressed
    pinMode(PIN_BTN_UP, INPUT_PULLUP);
    pinMode(PIN_BTN_DOWN, INPUT_PULLUP);
    pinMode(PIN_BTN_SELECT, INPUT_PULLUP);
    pinMode(PIN_BTN_BACK, INPUT_PULLUP);
}

// Low level reads (debouncing is handled by the App Framework input loop)
bool GPIOControl::isUpPressed() { 
    return digitalRead(PIN_BTN_UP) == LOW; 
}

bool GPIOControl::isDownPressed() { 
    return digitalRead(PIN_BTN_DOWN) == LOW; 
}

bool GPIOControl::isSelectPressed() { 
    return digitalRead(PIN_BTN_SELECT) == LOW; 
}

bool GPIOControl::isBackPressed() { 
    return digitalRead(PIN_BTN_BACK) == LOW; 
}