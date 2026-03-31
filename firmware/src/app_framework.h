#ifndef APP_FRAMEWORK_H
#define APP_FRAMEWORK_H

#include <string>

/**
 * @brief Base class for all Flipper "Apps" (Plugins).
 */
class BaseApp {
public:
    virtual ~BaseApp() {}
    virtual void start() = 0;
    virtual void tick() = 0;
    virtual void stop() = 0;
};

/**
 * @brief The root application that routes to other tools.
 */
class MainMenuApp : public BaseApp {
private:
    int selectedIndex = 0;
    const int NUM_ITEMS = 4;
    std::string menuItems[4] = {"Sub-GHz Radio", "NFC / RFID", "Infrared Code", "BadUSB"};

    // Simple time-based debouncing for navigation
    unsigned long lastButtonPress = 0;
    const unsigned long DEBOUNCE_DELAY = 150; 

public:
    void start() override;
    void tick() override;
    void stop() override;
};

#endif // APP_FRAMEWORK_H