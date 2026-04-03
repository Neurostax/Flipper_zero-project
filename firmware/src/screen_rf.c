#include "gui.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: RF TOOLS
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  status bar
//  ├────────────────────────────────┤
//  │ RF TOOLS       433.92MHz      │  header + freq
//  ├────────────────────────────────┤
//  │ > SubGHz Scanner              │  menu list (5 items, scroll)
//  │   Freq Analyzer               │
//  │   Raw Record                  │
//  │   Saved Signals               │
//  ├────────────────────────────────┤
//  │ [||||]  IDLE          ◀ ▶ adj │  status + freq adjust hint
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

#define RF_ITEM_COUNT   5
#define RF_VISIBLE      4
#define RF_ITEM_H       9
#define RF_LIST_Y       20

static const char *rf_items[RF_ITEM_COUNT] = {
    "SubGHz Scanner",
    "Freq Analyzer",
    "Raw Record",
    "Saved Signals",
    "Jam Mode",
};

static const char *rf_state_str[] = {
    "IDLE", "SCANNING", "RECORDING", "ANALYZING"
};

// Animated frequency spectrum — simple random-ish bars driven by tick
static void draw_spectrum(uint8_t x, uint8_t y, uint8_t tick) {
    // 16 bars, each 3px wide with 1px gap
    for (uint8_t b = 0; b < 16; b++) {
        // Pseudo-random height using tick + bar index
        uint8_t seed = (uint8_t)(b * 37 + tick * 3);
        uint8_t h    = (seed % 10) + 2;    // 2–11 px
        uint8_t bx   = x + b * 4;
        // Draw bar from bottom up
        for (uint8_t r = 0; r < h; r++) {
            draw_pixel(bx,     y - r, true);
            draw_pixel(bx + 1, y - r, true);
            draw_pixel(bx + 2, y - r, true);
        }
    }
}

// Scanning animation — horizontal sweep line
static void draw_scan_sweep(uint8_t y_top, uint8_t height, uint8_t tick) {
    uint8_t sweep_x = (tick * 2) % 124;
    // Bright sweep line
    draw_vline(sweep_x, y_top, height);
    // Faded trail (2 px behind)
    if (sweep_x >= 2) draw_vline(sweep_x - 2, y_top, height);
}

void screen_rf(GuiState *s) {
    draw_status_bar(s);
    RFContext *rf = &s->rf;

    // ── Header bar ────────────────────────────────────────────────────────
    draw_fill_rect(0, 9, 128, 8, true);

    ssd1306_display_text(&dev, 1, "RF TOOLS", 8, false);

    // Frequency display right-aligned
    char freq_buf[12];
    snprintf(freq_buf, sizeof(freq_buf), "%6.2fMHz", rf->frequency_mhz);
    ssd1306_display_text(&dev, 1, freq_buf, strlen(freq_buf), false);

    // ── Separator ─────────────────────────────────────────────────────────
    draw_hline(0, 17, 128);

    // ── Spectrum / scan visual (right half of screen, rows 18–44) ─────────
    if (rf->state == RF_SCANNING || rf->state == RF_ANALYZING) {
        draw_spectrum(64, 44, rf->bar_anim);
        draw_scan_sweep(18, 26, rf->bar_anim);
    } else {
        // Idle — static flat line with noise
        draw_hline(64, 36, 60);
        for (uint8_t i = 0; i < 60; i += 8) {
            uint8_t noise = (i * 13 + 7) % 4;
            draw_vline(64 + i, 34 - noise, noise * 2);
        }
    }

    // ── Menu list (left half) ─────────────────────────────────────────────
    uint8_t start = 0;
    if (rf->selected_item >= 2) start = rf->selected_item - 1;
    if (start + RF_VISIBLE > RF_ITEM_COUNT) start = RF_ITEM_COUNT - RF_VISIBLE;

    for (uint8_t i = 0; i < RF_VISIBLE; i++) {
        uint8_t idx = start + i;
        if (idx >= RF_ITEM_COUNT) break;
        uint8_t y       = RF_LIST_Y + i * RF_ITEM_H;
        bool    selected = (idx == rf->selected_item);
        uint8_t page     = y / 8;

        if (selected) {
            draw_fill_rect(0, y - 1, 62, RF_ITEM_H, true);
            char row[12];
            snprintf(row, sizeof(row), ">%.9s", rf_items[idx]);
            ssd1306_display_text(&dev, page, row, strlen(row), false);
        } else {
            char row[12];
            snprintf(row, sizeof(row), " %.9s", rf_items[idx]);
            ssd1306_display_text(&dev, page, row, strlen(row), true);
        }
    }

    // ── Divider between list and visual ───────────────────────────────────
    draw_vline(63, 17, 38);

    // ── Status bar bottom ─────────────────────────────────────────────────
    draw_hline(0, 55, 128);

    // Signal strength bars
    draw_signal_bars(2, 57, rf->signal_strength);

    // State label
    char state_buf[14];
    snprintf(state_buf, sizeof(state_buf), " %-10s", rf_state_str[rf->state]);
    ssd1306_display_text(&dev, 7, state_buf, strlen(state_buf), true);

    // Frequency adjust hint
    ssd1306_display_text(&dev, 7, "       <> FREQ", 14, true);
}
