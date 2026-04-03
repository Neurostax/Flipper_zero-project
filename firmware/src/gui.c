#include "gui.h"
#include <string.h>
#include <stdio.h>

// ─────────────────────────────────────────────────────────────────────────────
//  DISPLAY PRIMITIVE HELPERS
//  All pixel operations go through ssd1306_set_pixel so we work at the
//  raw 128×64 coordinate level — no page-boundary surprises.
// ─────────────────────────────────────────────────────────────────────────────

void draw_pixel(uint8_t x, uint8_t y, bool color) {
    if (x >= 128 || y >= 64) return;
    ssd1306_set_pixel(&dev, x, y, color);
}

void draw_hline(uint8_t x, uint8_t y, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) draw_pixel(x + i, y, true);
}

void draw_vline(uint8_t x, uint8_t y, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) draw_pixel(x, y + i, true);
}

void draw_rect_outline(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    draw_hline(x, y, w);
    draw_hline(x, y + h - 1, w);
    draw_vline(x, y, h);
    draw_vline(x + w - 1, y, h);
}

void draw_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color) {
    for (uint8_t row = 0; row < h; row++)
        for (uint8_t col = 0; col < w; col++)
            draw_pixel(x + col, y + row, color);
}

// Text using the driver's page-based API.
// page  = y / 8  (0–7)
// x_px  = pixel offset from left  (approximate — driver aligns to char width)
// invert = white text on black background when true
void draw_text_page(uint8_t page, uint8_t x_px, const char *text, bool invert) {
    // The nopnop2002 driver positions by character column; we convert x_px
    // to a rough char column using 6px-per-char (Font_6x8).
    // For sub-character accuracy use draw_pixel instead.
    (void)x_px;  // driver uses cursor internally — set before calling
    ssd1306_display_text(&dev, page, (char *)text, strlen(text), invert);
}

// ─────────────────────────────────────────────────────────────────────────────
//  SHARED WIDGETS
// ─────────────────────────────────────────────────────────────────────────────

// 5-bar signal strength indicator.  strength = 0–100
void draw_signal_bars(uint8_t x, uint8_t y, uint8_t strength) {
    uint8_t bars = (strength / 20);  // 0–5 bars
    for (uint8_t b = 0; b < 5; b++) {
        uint8_t bar_h = (b + 1) * 2;
        uint8_t bx = x + b * 4;
        uint8_t by = y + (10 - bar_h);
        draw_rect_outline(bx, by, 3, bar_h);
        if (b < bars) draw_fill_rect(bx + 1, by + 1, 1, bar_h - 2, true);
    }
}

// Compact battery icon  (9×5 px)  level = 0–100
void draw_battery_icon(uint8_t x, uint8_t y, uint8_t level) {
    // Shell
    draw_rect_outline(x, y, 7, 5);
    // Tip nub
    draw_pixel(x + 7, y + 1, true);
    draw_pixel(x + 7, y + 2, true);
    draw_pixel(x + 7, y + 3, true);
    // Fill
    uint8_t fill = (level * 5) / 100;
    if (fill > 0) draw_fill_rect(x + 1, y + 1, fill, 3, true);
}

// ─────────────────────────────────────────────────────────────────────────────
//  STATUS BAR  (page 0, 8 px tall, full-width inverted strip)
// ─────────────────────────────────────────────────────────────────────────────

// Battery level and RTC time must be supplied by your application layer.
// For now we expose weak symbols you can override.
__attribute__((weak)) uint8_t  app_battery_level(void)  { return 75; }
__attribute__((weak)) uint8_t  app_rtc_hour(void)       { return 12; }
__attribute__((weak)) uint8_t  app_rtc_minute(void)     { return 00; }

void draw_status_bar(GuiState *s) {
    (void)s;

    // Inverted background row
    draw_fill_rect(0, 0, 128, 8, true);

    // Device name (left, black-on-white = invert=false in driver terms)
    ssd1306_display_text(&dev, 0, "FLIP-X1", 7, false);

    // Clock  (centre-ish)
    char tbuf[6];
    snprintf(tbuf, sizeof(tbuf), "%02d:%02d", app_rtc_hour(), app_rtc_minute());
    // Position cursor to ~col 13 (13 * 6 = 78 px from left)
    // The driver's display_text always starts at col 0 on the page —
    // draw char-by-char using set_pixel for precise placement instead.
    // Simple approach: write at a fixed offset using spaces as padding.
    char tbuf_padded[17];
    snprintf(tbuf_padded, sizeof(tbuf_padded), "        %s", tbuf);
    ssd1306_display_text(&dev, 0, tbuf_padded, strlen(tbuf_padded), false);

    // Battery icon (pixel-level, top-right)
    draw_battery_icon(119, 2, app_battery_level());
}

// ─────────────────────────────────────────────────────────────────────────────
//  GUI INIT
// ─────────────────────────────────────────────────────────────────────────────

void gui_init(GuiState *state) {
    memset(state, 0, sizeof(GuiState));

    state->current    = SCREEN_MENU;
    state->menu_index = 0;
    state->tick       = 0;

    // RF defaults
    state->rf.frequency_mhz  = 433.92f;
    state->rf.signal_strength = 0;
    state->rf.state           = RF_IDLE;

    // NFC defaults
    state->nfc.state = NFC_IDLE;
    strncpy(state->nfc.uid, "--:--:--:--", sizeof(state->nfc.uid));
    strncpy(state->nfc.card_type, "NONE", sizeof(state->nfc.card_type));

    // IR defaults
    state->ir.selected_item = 0;
    state->ir.state         = IR_IDLE;

    // GPIO defaults — example pin map for ESP32 DevKit
    state->gpio.pins[0] = (GPIOPin){ "PA4", PIN_MODE_IN,  0 };
    state->gpio.pins[1] = (GPIOPin){ "PA5", PIN_MODE_OUT, 1 };
    state->gpio.pins[2] = (GPIOPin){ "PA6", PIN_MODE_IN,  0 };
    state->gpio.pins[3] = (GPIOPin){ "PA7", PIN_MODE_PWM, 65 };
    state->gpio.pins[4] = (GPIOPin){ "PB0", PIN_MODE_OUT, 0 };

    // Settings defaults
    state->settings.brightness  = 200;
    state->settings.flip_display = false;
    strncpy(state->settings.device_name, "FLIP-X1", sizeof(state->settings.device_name));
}

// ─────────────────────────────────────────────────────────────────────────────
//  RENDER DISPATCHER
// ─────────────────────────────────────────────────────────────────────────────

void gui_render(GuiState *state) {
    state->tick++;

    // Advance animation sub-ticks
    state->rf.bar_anim      = (state->rf.bar_anim      + 1) & 0xFF;
    state->nfc.pulse_tick   = (state->nfc.pulse_tick   + 1) & 0xFF;
    state->ir.wave_tick     = (state->ir.wave_tick     + 1) & 0xFF;
    state->gpio.pwm_tick    = (state->gpio.pwm_tick    + 1) & 0xFF;

    ssd1306_clear_screen(&dev, false);

    switch (state->current) {
        case SCREEN_MENU:     screen_menu(state);     break;
        case SCREEN_RF_TOOLS: screen_rf(state);       break;
        case SCREEN_NFC:      screen_nfc(state);      break;
        case SCREEN_IR:       screen_ir(state);       break;
        case SCREEN_GPIO:     screen_gpio(state);     break;
        case SCREEN_SETTINGS: screen_settings(state); break;
        default:              screen_menu(state);     break;
    }

    // Driver auto-pushes on each ssd1306_display_text call.
    // If using a framebuffer-only mode, call ssd1306_show_buffer(&dev) here.
}

// ─────────────────────────────────────────────────────────────────────────────
//  INPUT DISPATCHER
// ─────────────────────────────────────────────────────────────────────────────

#define MENU_ITEM_COUNT 6

void gui_input(GuiState *state, ButtonEvent btn) {
    switch (state->current) {

        // ── Main menu ──────────────────────────────────────────────────────
        case SCREEN_MENU:
            if (btn == BTN_UP && state->menu_index > 0)
                state->menu_index--;
            if (btn == BTN_DOWN && state->menu_index < MENU_ITEM_COUNT - 1)
                state->menu_index++;
            if (btn == BTN_OK)
                state->current = (ScreenID)(state->menu_index + 1);
            break;

        // ── RF Tools ──────────────────────────────────────────────────────
        case SCREEN_RF_TOOLS:
            if (btn == BTN_BACK) { state->current = SCREEN_MENU; break; }
            if (btn == BTN_UP   && state->rf.selected_item > 0)
                state->rf.selected_item--;
            if (btn == BTN_DOWN && state->rf.selected_item < 4)
                state->rf.selected_item++;
            if (btn == BTN_OK) {
                // Toggle scan on the selected item
                state->rf.state = (state->rf.state == RF_IDLE) ? RF_SCANNING : RF_IDLE;
            }
            if (btn == BTN_LEFT)  state->rf.frequency_mhz -= 0.05f;
            if (btn == BTN_RIGHT) state->rf.frequency_mhz += 0.05f;
            break;

        // ── NFC ───────────────────────────────────────────────────────────
        case SCREEN_NFC:
            if (btn == BTN_BACK) { state->current = SCREEN_MENU; break; }
            if (btn == BTN_OK) {
                if (state->nfc.state == NFC_IDLE)
                    state->nfc.state = NFC_SCANNING;
                else
                    state->nfc.state = NFC_IDLE;
            }
            break;

        // ── IR Blaster ────────────────────────────────────────────────────
        case SCREEN_IR:
            if (btn == BTN_BACK) { state->current = SCREEN_MENU; break; }
            if (btn == BTN_UP   && state->ir.selected_item > 0)
                state->ir.selected_item--;
            if (btn == BTN_DOWN && state->ir.selected_item < 4)
                state->ir.selected_item++;
            if (btn == BTN_OK)
                state->ir.state = IR_SENDING;
            break;

        // ── GPIO ──────────────────────────────────────────────────────────
        case SCREEN_GPIO:
            if (btn == BTN_BACK) { state->current = SCREEN_MENU; break; }
            if (btn == BTN_UP   && state->gpio.selected_pin > 0)
                state->gpio.selected_pin--;
            if (btn == BTN_DOWN && state->gpio.selected_pin < GUI_GPIO_PIN_COUNT - 1)
                state->gpio.selected_pin++;
            if (btn == BTN_OK) {
                // Toggle output pins; adjust PWM
                GPIOPin *pin = &state->gpio.pins[state->gpio.selected_pin];
                if (pin->mode == PIN_MODE_OUT)
                    pin->value ^= 1;
                else if (pin->mode == PIN_MODE_PWM && pin->value < 100)
                    pin->value += 10;
            }
            if (btn == BTN_LEFT) {
                GPIOPin *pin = &state->gpio.pins[state->gpio.selected_pin];
                if (pin->mode == PIN_MODE_PWM && pin->value >= 10)
                    pin->value -= 10;
            }
            break;

        // ── Settings ──────────────────────────────────────────────────────
        case SCREEN_SETTINGS:
            if (btn == BTN_BACK) { state->current = SCREEN_MENU; break; }
            if (btn == BTN_UP   && state->settings.selected_item > 0)
                state->settings.selected_item--;
            if (btn == BTN_DOWN && state->settings.selected_item < SETTINGS_ITEM_COUNT - 1)
                state->settings.selected_item++;
            if (btn == BTN_OK || btn == BTN_RIGHT) {
                switch (state->settings.selected_item) {
                    case 0: // Brightness +
                        if (state->settings.brightness < 240)
                            state->settings.brightness += 15;
                        ssd1306_contrast(&dev, state->settings.brightness);
                        break;
                    case 1: // Flip display
                        state->settings.flip_display = !state->settings.flip_display;
                        // ssd1306_flip(&dev, state->settings.flip_display);
                        break;
                }
            }
            if (btn == BTN_LEFT) {
                if (state->settings.selected_item == 0 &&
                    state->settings.brightness > 15)
                    state->settings.brightness -= 15;
                    ssd1306_contrast(&dev, state->settings.brightness);
            }
            break;

        default: break;
    }
}
