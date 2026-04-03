#include "gui.h"
#include <stdio.h>
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: GPIO MONITOR
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  status bar
//  ├────────────────────────────────┤
//  │ GPIO MONITOR                  │  title
//  ├────────────────────────────────┤
//  │ PIN  MODE  STATE   VALUE      │  column headers
//  ├────────────────────────────────┤
//  │ PA4  IN    [HI]    ─────      │  pin rows (5 pins)
//  │>PA5  OUT   [LO]    [■■■  ]    │  selected pin highlighted
//  │ PA6  IN    [HI]    ─────      │
//  │ PA7  PWM   65%     [■■■■ ]    │
//  │ PB0  OUT   [LO]    ─────      │
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

#define PIN_ROW_H    9
#define PIN_LIST_Y   27   // y of first pin row
#define PIN_COL_NAME  2
#define PIN_COL_MODE 20
#define PIN_COL_STATE 38
#define PIN_COL_BAR   62

static const char *mode_labels[] = { "IN ", "OUT", "PWM" };

// Draw a small HI/LO state badge
static void draw_state_badge(uint8_t x, uint8_t y, bool high, bool selected) {
    uint8_t w = 10, h = 7;
    if (selected) {
        draw_fill_rect(x, y, w, h, !high);
        draw_rect_outline(x, y, w, h);
        // Text drawn outside — driver can't do sub-char positioning cleanly here
    } else {
        draw_rect_outline(x, y, w, h);
    }
    // Fill interior for HI
    if (high) draw_fill_rect(x + 1, y + 1, w - 2, h - 2, !selected);
}

// Draw a compact digital waveform (recent history) — simulated from tick
static void draw_digital_wave(uint8_t x, uint8_t y, uint8_t tick, bool current_val) {
    uint8_t w = 50;
    uint8_t amplitude = 4;

    // Simulate 8 transitions worth of history
    for (uint8_t i = 0; i < w; i++) {
        uint8_t seg   = i / (w / 8);
        bool    state = ((tick + seg) & 1) ^ (current_val ? 0 : 1);
        uint8_t py    = state ? (y - amplitude) : y;
        draw_pixel(x + i, py, true);

        // Draw transitions (vertical edges)
        if (i > 0) {
            uint8_t prev_seg   = (i - 1) / (w / 8);
            bool    prev_state = ((tick + prev_seg) & 1) ^ (current_val ? 0 : 1);
            if (state != prev_state) {
                draw_vline(x + i, y - amplitude, amplitude + 1);
            }
        }
    }
}

// Draw a PWM duty cycle bar
static void draw_pwm_bar(uint8_t x, uint8_t y, uint8_t duty_pct) {
    uint8_t bar_w = 50, bar_h = 6;
    draw_rect_outline(x, y, bar_w, bar_h);

    uint8_t fill_w = (uint8_t)((duty_pct * (bar_w - 2)) / 100);
    if (fill_w > 0)
        draw_fill_rect(x + 1, y + 1, fill_w, bar_h - 2, true);

    // Duty % label after bar
    char pct_buf[5];
    snprintf(pct_buf, sizeof(pct_buf), "%3d%%", duty_pct);
    ssd1306_display_text(&dev, (y) / 8, pct_buf, 4, true);
}

void screen_gpio(GuiState *s) {
    draw_status_bar(s);
    GPIOContext *gpio = &s->gpio;

    // ── Title ─────────────────────────────────────────────────────────────
    draw_fill_rect(0, 9, 128, 8, true);
    ssd1306_display_text(&dev, 1, "GPIO MONITOR", 12, false);

    // ── Column headers ────────────────────────────────────────────────────
    draw_hline(0, 17, 128);
    ssd1306_display_text(&dev, 2, "PIN MODE ST  VALUE", 18, true);
    draw_hline(0, 26, 128);

    // ── Pin rows ──────────────────────────────────────────────────────────
    for (uint8_t i = 0; i < GUI_GPIO_PIN_COUNT; i++) {
        GPIOPin *pin     = &gpio->pins[i];
        uint8_t  y       = PIN_LIST_Y + i * PIN_ROW_H;
        uint8_t  page    = y / 8;
        bool     selected = (i == gpio->selected_pin);

        if (selected) {
            draw_fill_rect(0, y - 1, 60, PIN_ROW_H, true);
        }

        // Pin name
        char row[8];
        snprintf(row, sizeof(row), "%c%.3s", selected ? '>' : ' ', pin->name);
        ssd1306_display_text(&dev, page, row, 4, selected ? false : true);

        // Mode label
        char mode_row[6];
        snprintf(mode_row, sizeof(mode_row), "    %s", mode_labels[pin->mode]);
        ssd1306_display_text(&dev, page, mode_row, 7, selected ? false : true);

        // State badge area (text-only approximation)
        if (pin->mode == PIN_MODE_IN || pin->mode == PIN_MODE_OUT) {
            const char *state_str = pin->value ? "HI" : "LO";
            char st_row[12];
            snprintf(st_row, sizeof(st_row), "       %s", state_str);
            ssd1306_display_text(&dev, page, st_row, strlen(st_row),
                                  selected ? false : true);
        } else {
            char pwm_row[12];
            snprintf(pwm_row, sizeof(pwm_row), "       %2d%%", pin->value);
            ssd1306_display_text(&dev, page, pwm_row, strlen(pwm_row),
                                  selected ? false : true);
        }

        // Value visualisation (right half)
        if (pin->mode == PIN_MODE_PWM) {
            draw_pwm_bar(PIN_COL_BAR, y, pin->value);
        } else {
            // Digital waveform
            draw_digital_wave(PIN_COL_BAR, y + 5, gpio->pwm_tick + i * 13, pin->value);
        }
    }

    // ── Hint row ──────────────────────────────────────────────────────────
    if (GUI_GPIO_PIN_COUNT * PIN_ROW_H + PIN_LIST_Y < 56) {
        draw_hline(0, 55, 128);
        ssd1306_display_text(&dev, 7, "OK:TGL  <>:PWM ADJ", 18, true);
    }
}
