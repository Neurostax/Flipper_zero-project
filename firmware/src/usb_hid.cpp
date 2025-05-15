#include "usb_hid.h"
#include "fap.h" // Flipper API for USB HID

USBHID::USBHID() {}
USBHID::~USBHID() {}

void USBHID::initialize() {
    // Initialize USB HID
}

void USBHID::sendKeyboardInput(const std::string& text) {
    fap_usb_hid_send_keyboard(text.c_str());
}

void USBHID::emulateMouse(int x, int y, bool click) {
    fap_usb_hid_move_mouse(x, y);
    if (click) {
        fap_usb_hid_mouse_click();
    }
}