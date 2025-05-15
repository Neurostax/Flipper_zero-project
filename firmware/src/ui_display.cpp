#include "ui_display.h"
#include "fap.h" // Flipper API for display

#include <string>

UIDisplay::UIDisplay() {}
UIDisplay::~UIDisplay() {}

void UIDisplay::initialize() {
    fap_display_init();
}

void UIDisplay::clear() {
    fap_display_clear();
}

void UIDisplay::drawText(int x, int y, const std::string& text) {
    fap_display_draw_text(x, y, text.c_str());
}

void UIDisplay::drawRectangle(int x, int y, int width, int height) {
    fap_display_draw_rect(x, y, width, height);
}

void UIDisplay::update() {
    fap_display_update();
}

void UIDisplay::showText(const std::string& message) {
    clear();
    drawText(10, 10, message);
    update();
}