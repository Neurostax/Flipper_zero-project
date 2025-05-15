#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

/**
 * @brief Handles drawing on the device display.
 */
class UIDisplay {
public:
    UIDisplay();
    ~UIDisplay();

    /**
     * @brief Initializes display.
     */
    void initialize();

    /**
     * @brief Clears the display.
     */
    void clear();

    /**
     * @brief Draws text at specified position.
     */
    void drawText(int x, int y, const std::string& text);

    /**
     * @brief Draws a rectangle.
     */
    void drawRectangle(int x, int y, int width, int height);

    /**
     * @brief Updates the display to show changes.
     */
    void update();

    /**
     * @brief Shows a simple text message.
     */
    void showText(const std::string& message);
};

#endif // UI_DISPLAY_H