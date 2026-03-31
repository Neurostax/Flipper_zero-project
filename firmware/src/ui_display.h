#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <string>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

/**
 * @brief Hardware Abstraction Layer for the OLED Display.
 */
class UIDisplay {
private:
    Adafruit_SSD1306* oled;

public:
    UIDisplay();
    ~UIDisplay();

    void initialize();
    void clear();
    void drawText(int x, int y, const std::string& text);
    void drawRectangle(int x, int y, int width, int height);
    void update();
    void showText(const std::string& message);
};

#endif // UI_DISPLAY_H