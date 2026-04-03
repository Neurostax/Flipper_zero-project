#include "gui.h"
#include <string.h>
#include <stdio.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: MAIN MENU
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  ← status bar  (page 0, y 0–7)
//  ├────────────────────────────────┤
//  │ ~ RF Tools                  > │  ← item rows   (pages 1–7)
//  │ # NFC/RFID                  > │    each 13 px tall
//  │ ^ IR Blaster                > │    4 visible at a time
//  │ : GPIO                      > │
//  │                          [||] │  ← scrollbar
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

#define MENU_COUNT    6
#define MENU_VISIBLE  4
#define ITEM_H        13      // pixels per row
#define MENU_Y_START  10      // first row top (below status bar)

typedef struct {
    const char icon;
    const char *label;
} MenuItem;

static const MenuItem menu_items[MENU_COUNT] = {
    { '~', "RF Tools"   },
    { '#', "NFC/RFID"   },
    { '^', "IR Blaster" },
    { ':', "GPIO"       },
    { '*', "BLE Scan"   },
    { '@', "Settings"   },
};

// Draw a tiny 3-px wide icon glyph using pixels
static void draw_icon(uint8_t x, uint8_t y, char icon) {
    switch (icon) {
        case '~': // wave — RF
            draw_pixel(x,   y+1, true); draw_pixel(x+1, y,   true);
            draw_pixel(x+2, y+1, true); draw_pixel(x+3, y+2, true);
            draw_pixel(x+4, y+1, true);
            break;
        case '#': // grid — NFC
            draw_hline(x, y,   5); draw_hline(x, y+2, 5); draw_hline(x, y+4, 5);
            draw_vline(x+1, y, 5); draw_vline(x+3, y, 5);
            break;
        case '^': // arrow up — IR
            draw_pixel(x+2, y,   true);
            draw_pixel(x+1, y+1, true); draw_pixel(x+2, y+1, true); draw_pixel(x+3, y+1, true);
            draw_hline(x, y+2, 5); draw_hline(x+1, y+3, 3);
            break;
        case ':': // two dots — GPIO
            draw_fill_rect(x+1, y+1,   2, 2, true);
            draw_fill_rect(x+1, y+3,   2, 2, true);
            break;
        case '*': // asterisk — BLE
            draw_pixel(x+2, y,   true); draw_pixel(x+2, y+4, true);
            draw_pixel(x,   y+2, true); draw_pixel(x+4, y+2, true);
            draw_pixel(x+1, y+1, true); draw_pixel(x+3, y+1, true);
            draw_pixel(x+1, y+3, true); draw_pixel(x+3, y+3, true);
            draw_pixel(x+2, y+2, true);
            break;
        case '@': // gear — Settings
            draw_rect_outline(x+1, y+1, 3, 3);
            draw_pixel(x+2, y,   true); draw_pixel(x+2, y+4, true);
            draw_pixel(x,   y+2, true); draw_pixel(x+4, y+2, true);
            break;
        default: break;
    }
}

void screen_menu(GuiState *s) {
    draw_status_bar(s);

    // Compute scroll offset so selected item stays in view
    uint8_t start = 0;
    if (s->menu_index >= 2)
        start = s->menu_index - 1;
    if (start + MENU_VISIBLE > MENU_COUNT)
        start = MENU_COUNT - MENU_VISIBLE;

    for (uint8_t i = 0; i < MENU_VISIBLE; i++) {
        uint8_t idx = start + i;
        if (idx >= MENU_COUNT) break;

        uint8_t y       = MENU_Y_START + i * ITEM_H;
        bool    selected = (idx == s->menu_index);

        if (selected) {
            // Full-width highlight bar
            draw_fill_rect(0, y - 1, 124, ITEM_H, true);

            // Icon (inverted = drawn on white bg so use clear pixels trick:
            // fill the icon area white then draw black dots)
            // Simplest: redraw icon in black — we set pixels to false (off)
            // after filling the row white.
            // We draw the icon to a temp buffer by toggling pixel state.

            // Label — invert text (black on white)
            char row[22];
            snprintf(row, sizeof(row), "  %s", menu_items[idx].label);
            ssd1306_display_text(&dev, (y) / 8, row, strlen(row), false);

            // Arrow indicator right edge
            draw_pixel(121, y + 3, false);
            draw_pixel(122, y + 4, false);
            draw_pixel(121, y + 5, false);
        } else {
            // Normal row — draw icon then label
            char row[22];
            snprintf(row, sizeof(row), "  %s", menu_items[idx].label);
            ssd1306_display_text(&dev, (y) / 8, row, strlen(row), true);
        }

        // Draw icon (pixel-drawn, works on both selected and normal rows)
        // On selected rows the icon is drawn after the inverted fill.
        draw_icon(2, y + 2, menu_items[idx].icon);
    }

    // ── Scrollbar (2 px wide, right edge, below status bar) ──────────────
    uint8_t content_h  = 64 - MENU_Y_START;
    uint8_t bar_h      = (MENU_VISIBLE * content_h) / MENU_COUNT;
    uint8_t bar_y      = MENU_Y_START + (start * content_h) / MENU_COUNT;

    draw_vline(126, MENU_Y_START, content_h);                    // track
    draw_fill_rect(126, bar_y, 2, bar_h, true);                  // thumb

    // ── Bottom hint ───────────────────────────────────────────────────────
    // Tiny "OK=open" hint drawn at page 7 far right — only when no overlap
    if (MENU_Y_START + MENU_VISIBLE * ITEM_H < 56) {
        ssd1306_display_text(&dev, 7, "             OK:OPEN", 20, true);
    }
}
