#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <Arduino.h>

/**
 * @brief Hardware Abstraction Layer for GPIO buttons.
 */
class GPIOControl {
public:
    void initialize();
    
    // Returns true if button is currently PRESSED (active-low managed internally)
    bool isUpPressed();
    bool isDownPressed();
    bool isSelectPressed();
    bool isBackPressed();
};

#endif // GPIO_CONTROL_H