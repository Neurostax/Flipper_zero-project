#ifndef USB_HID_H
#define USB_HID_H

#include <string>
#include <vector>
#include <cstdint>

// Key modifier masks (for key combinations)
enum KeyModifier {
    MOD_NONE      = 0x00,
    MOD_LEFT_CTRL = 0x01,
    MOD_LEFT_SHIFT = 0x02,
    MOD_LEFT_ALT  = 0x04,
    MOD_LEFT_GUI  = 0x08,  // Windows key / Command key
    MOD_RIGHT_CTRL = 0x10,
    MOD_RIGHT_SHIFT = 0x20,
    MOD_RIGHT_ALT = 0x40,
    MOD_RIGHT_GUI = 0x80
};

// Media and special keys
enum SpecialKey {
    KEY_NONE = 0x00,
    // Modifiers
    KEY_CTRL = 0x01,
    KEY_SHIFT = 0x02,
    KEY_ALT = 0x04,
    KEY_GUI = 0x08,
    // Navigation
    KEY_UP = 0x52,
    KEY_DOWN = 0x51,
    KEY_LEFT = 0x50,
    KEY_RIGHT = 0x4F,
    KEY_HOME = 0x4A,
    KEY_END = 0x4D,
    KEY_PAGE_UP = 0x4B,
    KEY_PAGE_DOWN = 0x4E,
    KEY_INSERT = 0x49,
    KEY_DELETE = 0x4C,
    // Editing
    KEY_BACKSPACE = 0x2A,
    KEY_TAB = 0x2B,
    KEY_ENTER = 0x28,
    KEY_ESC = 0x29,
    KEY_SPACE = 0x2C,
    // Function keys
    KEY_F1 = 0x3A,
    KEY_F2 = 0x3B,
    KEY_F3 = 0x3C,
    KEY_F4 = 0x3D,
    KEY_F5 = 0x3E,
    KEY_F6 = 0x3F,
    KEY_F7 = 0x40,
    KEY_F8 = 0x41,
    KEY_F9 = 0x42,
    KEY_F10 = 0x43,
    KEY_F11 = 0x44,
    KEY_F12 = 0x45,
    // Lock keys
    KEY_CAPS_LOCK = 0x39,
    KEY_NUM_LOCK = 0x53,
    KEY_SCROLL_LOCK = 0x47
};

// Mouse buttons
enum MouseButton {
    MOUSE_BUTTON_NONE = 0x00,
    MOUSE_BUTTON_LEFT = 0x01,
    MOUSE_BUTTON_RIGHT = 0x02,
    MOUSE_BUTTON_MIDDLE = 0x04,
    MOUSE_BUTTON_BACK = 0x08,
    MOUSE_BUTTON_FORWARD = 0x10
};

// Keyboard LED states
struct KeyboardLEDs {
    bool numLock;
    bool capsLock;
    bool scrollLock;
    bool compose;
    bool kana;
};

// HID Report structures
struct KeyboardReport {
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keys[6];
};

struct MouseReport {
    uint8_t buttons;
    int16_t x;
    int16_t y;
    int8_t wheel;
    int8_t pan;  // Horizontal wheel
};

/**
 * @brief Complete USB HID implementation for keyboard and mouse emulation
 */
class USBHID {
public:
    USBHID();
    ~USBHID();

    // ========== INITIALIZATION ==========
    void initialize();
    bool isConnected();
    void setPollingInterval(uint8_t interval_ms);

    // ========== COMPLETE KEYBOARD FUNCTIONALITY ==========
    
    // Basic text input (handles all ASCII characters)
    void sendText(const std::string& text);
    void sendText(const char* text);
    void sendChar(char c);
    
    // Key press/release with modifiers
    void pressKey(uint8_t modifier, uint8_t key);
    void releaseKey(uint8_t modifier, uint8_t key);
    void tapKey(uint8_t modifier, uint8_t key);
    void tapKey(SpecialKey key);
    
    // Multiple keys simultaneously (e.g., Ctrl+Alt+Del)
    void pressMultipleKeys(uint8_t modifier, const std::vector<uint8_t>& keys);
    void releaseAllKeys();
    
    // Common keyboard shortcuts
    void sendShortcut(uint8_t modifier, uint8_t key);
    void sendCtrlAltDel();
    void sendAltTab();
    void sendWinKey();
    void sendCopy();
    void sendPaste();
    void sendCut();
    void sendUndo();
    void sendSelectAll();
    
    // Media keys
    void sendMediaPlayPause();
    void sendMediaStop();
    void sendMediaNext();
    void sendMediaPrev();
    void sendVolumeUp();
    void sendVolumeDown();
    void sendVolumeMute();
    
    // System keys
    void sendPowerKey();
    void sendSleepKey();
    void sendWakeKey();
    
    // LED status (read current keyboard LED states)
    KeyboardLEDs getKeyboardLEDs();
    bool isNumLockOn();
    bool isCapsLockOn();
    bool isScrollLockOn();
    
    // ========== COMPLETE MOUSE FUNCTIONALITY ==========
    
    // Relative movement (standard)
    void moveMouse(int16_t x, int16_t y);
    void moveMouseSmooth(int16_t x, int16_t y, uint8_t steps);
    
    // Absolute positioning (for touchscreens/tablets)
    void moveMouseTo(uint16_t x, uint16_t y, uint16_t screenWidth, uint16_t screenHeight);
    
    // Mouse clicks
    void click(MouseButton button);
    void doubleClick(MouseButton button);
    void rightClick();
    void middleClick();
    
    // Press and hold
    void pressButton(MouseButton button);
    void releaseButton(MouseButton button);
    
    // Scroll wheel
    void scroll(int8_t lines);
    void scrollHorizontal(int8_t lines);
    void smoothScroll(int8_t lines, uint8_t duration_ms);
    
    // Drag and drop
    void drag(int16_t fromX, int16_t fromY, int16_t toX, int16_t toY);
    void dragAndDrop(int16_t fromX, int16_t fromY, int16_t toX, int16_t toY);
    
    // ========== ADVANCED HID FEATURES ==========
    
    // Raw HID reports (for custom HID devices)
    void sendRawReport(const uint8_t* data, size_t length);
    
    // Consumer control (multimedia)
    void sendConsumerControl(uint16_t usage);
    
    // Game controller emulation
    void setGamepadState(uint8_t buttons, int16_t x, int16_t y, int16_t z, int16_t rz);
    
    // Macro recording and playback
    void startMacro();
    void stopMacro();
    void playMacro();
    void saveMacro(const std::string& filename);
    void loadMacro(const std::string& filename);
    
    // Key state tracking
    bool isKeyPressed(uint8_t key);
    std::vector<uint8_t> getPressedKeys();
    
private:
    struct Impl;
    Impl* pImpl;
};

#endif // USB_HID_H