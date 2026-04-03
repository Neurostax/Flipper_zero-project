#include "gui.h"
#include <stdio.h>
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: SETTINGS
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  status bar
//  ├────────────────────────────────┤
//  │ SETTINGS                      │  title
//  ├────────────────────────────────┤
//  │ > Brightness   [███████   ]   │  item + slider/value
//  │   Orientation  [NORMAL]       │
//  │   Device Name  FLIP-X1        │
//  │   About                       │
//  ├────────────────────────────────┤
//  │ <>:ADJUST   OK:TOGGLE         │  hint bar
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

#define SETTINGS_Y_START  19
#define SETTINGS_ITEM_H   10
#define VALUE_COL          64    // x offset for value widgets

// Draw a horizontal slider for a 0–255 value
static void draw_slider(uint8_t x, uint8_t y, uint8_t value) {
    uint8_t w = 58, h = 6;
    draw_rect_outline(x, y, w, h);
    uint8_t fill = (uint8_t)((value * (uint16_t)(w - 2)) / 255);
    if (fill > 0) draw_fill_rect(x + 1, y + 1, fill, h - 2, true);
    // Thumb indicator
    draw_vline(x + 1 + fill, y - 1, h + 2);
}

// Draw a toggle badge [ON] or [OFF]
static void draw_toggle(uint8_t x, uint8_t y, bool on) {
    const char *label = on ? "[ON ]" : "[OFF]";
    ssd1306_display_text(&dev, y / 8, label, 5, on);
}

// Draw "about" content — firmware info panel
static void draw_about_panel(void) {
    ssd1306_display_text(&dev, 3, "  FLIP-X1 DEVICE", 16, true);
    ssd1306_display_text(&dev, 4, "  FW:  v0.1.0", 13, true);
    ssd1306_display_text(&dev, 5, "  MCU: ESP32-WROOM", 18, true);
    ssd1306_display_text(&dev, 6, "  OLED:SSD1306 128x64", 21, true);
    ssd1306_display_text(&dev, 7, "  github.com/flipx1", 19, true);
}

// Settings item definitions
typedef struct {
    const char *label;
} SettingsItem;

static const SettingsItem settings_items[SETTINGS_ITEM_COUNT] = {
    { "Brightness" },
    { "Orientation" },
    { "Device Name" },
    { "About" },
};

void screen_settings(GuiState *s) {
    draw_status_bar(s);
    SettingsContext *cfg = &s->settings;

    // ── Title ─────────────────────────────────────────────────────────────
    draw_fill_rect(0, 9, 128, 8, true);
    ssd1306_display_text(&dev, 1, "SETTINGS", 8, false);

    draw_hline(0, 17, 128);

    // ── If "About" is selected, show the about panel instead of list ──────
    if (cfg->selected_item == 3) {
        // Still show the about item as selected at top for context
        draw_fill_rect(0, SETTINGS_Y_START - 1, 128, SETTINGS_ITEM_H, true);
        ssd1306_display_text(&dev, SETTINGS_Y_START / 8, ">About", 6, false);
        draw_hline(0, SETTINGS_Y_START + SETTINGS_ITEM_H - 1, 128);

        draw_about_panel();
        return;
    }

    // ── Settings list ─────────────────────────────────────────────────────
    for (uint8_t i = 0; i < SETTINGS_ITEM_COUNT; i++) {
        uint8_t y        = SETTINGS_Y_START + i * SETTINGS_ITEM_H;
        uint8_t page     = y / 8;
        bool    selected  = (i == cfg->selected_item);

        if (selected) {
            draw_fill_rect(0, y - 1, 128, SETTINGS_ITEM_H, true);
            char row[14];
            snprintf(row, sizeof(row), ">%.11s", settings_items[i].label);
            ssd1306_display_text(&dev, page, row, strlen(row), false);
        } else {
            char row[14];
            snprintf(row, sizeof(row), " %.11s", settings_items[i].label);
            ssd1306_display_text(&dev, page, row, strlen(row), true);
        }

        // Value widgets (right half)
        switch (i) {
            case 0:  // Brightness slider
                draw_slider(VALUE_COL, y, cfg->brightness);
                break;

            case 1:  // Orientation toggle
                draw_toggle(VALUE_COL, y, !cfg->flip_display);
                break;

            case 2: { // Device name (truncated)
                char name_buf[12];
                snprintf(name_buf, sizeof(name_buf), "%.10s", cfg->device_name);
                ssd1306_display_text(&dev, page, name_buf, strlen(name_buf),
                                      selected ? false : true);
                break;
            }

            case 3:  // About — arrow hint
                ssd1306_display_text(&dev, page, "       [ENTER >]", 16,
                                      selected ? false : true);
                break;
        }
    }

    // ── Divider + hint ────────────────────────────────────────────────────
    uint8_t hint_y = SETTINGS_Y_START + SETTINGS_ITEM_COUNT * SETTINGS_ITEM_H;
    if (hint_y < 57) {
        draw_hline(0, hint_y, 128);
        ssd1306_display_text(&dev, hint_y / 8 + 1, "<>:ADJUST OK:SELECT", 19, true);
    }

    // ── Version string (very bottom, always visible) ──────────────────────
    ssd1306_display_text(&dev, 7, "FLIP-X1 FW v0.1.0", 17, true);
}
