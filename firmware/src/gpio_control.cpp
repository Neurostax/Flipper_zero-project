#include "gpio_control.h"
#include "fap.h" // Flipper API for GPIO

#include <thread>
#include <chrono>

GPIOControl::GPIOControl() {}
GPIOControl::~GPIOControl() {}

void GPIOControl::initialize() {
    // Initialization code if needed
}

/**
 * Sets the GPIO pin as output
 */
void GPIOControl::setPinOutput(uint8_t pin) {
    fap_gpio_set_direction(pin, FAP_GPIO_DIR_OUTPUT);
}

/**
 * Write HIGH to GPIO pin
 */
void GPIOControl::writePinHigh(uint8_t pin) {
    fap_gpio_write(pin, true);
}

/**
 * Write LOW to GPIO pin
 */
void GPIOControl::writePinLow(uint8_t pin) {
    fap_gpio_write(pin, false);
}

/**
 * Read GPIO pin state
 */
bool GPIOControl::readPin(uint8_t pin) {
    return fap_gpio_read(pin);
}

/**
 * Toggle GPIO pin state
 */
void GPIOControl::togglePin(uint8_t pin) {
    bool current = fap_gpio_read(pin);
    fap_gpio_write(pin, !current);
}

/**
 * Blink an LED connected to the specified GPIO pin
 */
void GPIOControl::blinkLED(uint8_t pin, uint32_t duration_ms, uint8_t blink_count) {
    setPinOutput(pin);
    for (uint8_t i = 0; i < blink_count; ++i) {
        writePinHigh(pin);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
        writePinLow(pin);
        std::this_thread::sleep_for(std::chrono::milliseconds(duration_ms));
    }
}