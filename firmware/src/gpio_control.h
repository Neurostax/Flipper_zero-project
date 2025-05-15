#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <cstdint>

/**
 * @brief Handles GPIO control: reading, writing, toggling pins, blinking LEDs.
 */
class GPIOControl {
public:
    GPIOControl();
    ~GPIOControl();

    /**
     * @brief Initializes GPIO subsystem.
     */
    void initialize();

    /**
     * @brief Sets the specified GPIO pin as output.
     * @param pin GPIO pin number.
     */
    void setPinOutput(uint8_t pin);

    /**
     * @brief Sets the specified GPIO pin HIGH.
     * @param pin GPIO pin number.
     */
    void writePinHigh(uint8_t pin);

    /**
     * @brief Sets the specified GPIO pin LOW.
     * @param pin GPIO pin number.
     */
    void writePinLow(uint8_t pin);

    /**
     * @brief Reads the current state of a GPIO pin.
     * @param pin GPIO pin number.
     * @return true if HIGH, false if LOW.
     */
    bool readPin(uint8_t pin);

    /**
     * @brief Toggles the state of a GPIO pin.
     * @param pin GPIO pin number.
     */
    void togglePin(uint8_t pin);

    /**
     * @brief Blinks an LED connected to a GPIO pin.
     * @param pin GPIO pin number.
     * @param duration_ms Duration to keep the LED ON in milliseconds.
     * @param blink_count Number of blink cycles.
     */
    void blinkLED(uint8_t pin, uint32_t duration_ms, uint8_t blink_count = 3);

private:
    // Internal helper functions can be added here
};

#endif // GPIO_CONTROL_H