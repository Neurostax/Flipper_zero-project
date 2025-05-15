#ifndef USB_HID_H
#define USB_HID_H

#include <string>

/**
 * @brief Handles USB HID emulation for keyboard and mouse.
 */
class USBHID {
public:
    USBHID();
    ~USBHID();

    /**
     * @brief Initializes USB HID interface.
     */
    void initialize();

    /**
     * @brief Sends keyboard input.
     * @param text Text to send.
     */
    void sendKeyboardInput(const std::string& text);

    /**
     * @brief Emulates mouse movement and clicks.
     * @param x X movement.
     * @param y Y movement.
     * @param click Whether to click.
     */
    void emulateMouse(int x, int y, bool click);

private:
    // Internal state
};

#endif // USB_HID_H