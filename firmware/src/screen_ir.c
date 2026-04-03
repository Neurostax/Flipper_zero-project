#include "gui.h"
#include <stdio.h>
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: IR BLASTER
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  status bar
//  ├────────────────────────────────┤
//  │ IR BLASTER         38kHz      │  header
//  ├────────────────────────────────┤
//  │ > TV POWER                    │  command list
//  │   VOL UP                      │
//  │   VOL DOWN                    │
//  │   MUTE                        │
//  ├────────────────────────────────┤
//  │ [~~carrier wave~~]   IDLE     │  IR wave + state
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

#define IR_ITEM_COUNT  5
#define IR_VISIBLE     4
#define IR_ITEM_H      9
#define IR_LIST_Y      19

static const char *ir_commands[IR_ITEM_COUNT] = {
    "TV POWER",
    "VOL UP",
    "VOL DOWN",
    "MUTE",
    "CH NEXT",
};

static const char *ir_protocols[IR_ITEM_COUNT] = {
    "NEC",
    "NEC",
    "NEC",
    "RC5",
    "RC5",
};

// IR carrier wave — 38kHz rendered as a square wave across the bottom panel
static void draw_carrier_wave(uint8_t x, uint8_t y, uint8_t wave_tick, bool active) {
    uint8_t wave_w = 80;
    uint8_t amplitude = 4;
    uint8_t period    = 8;   // pixels per cycle

    for (uint8_t i = 0; i < wave_w; i++) {
        // Square wave — high for first half of period, low for second half
        bool high = (((i + wave_tick) % period) < (period / 2));

        // When not sending, show a flat line with occasional noise
        if (!active) {
            draw_pixel(x + i, y, true);
            continue;
        }

        if (high) {
            // High state: draw vertical bar up then horizontal top
            draw_pixel(x + i, y, true);
            draw_pixel(x + i, y - amplitude, true);
            // Fill the vertical transition
            if (i > 0) {
                bool prev_high = ((( i - 1 + wave_tick) % period) < (period / 2));
                if (!prev_high) draw_vline(x + i, y - amplitude, amplitude + 1);
            }
        } else {
            draw_pixel(x + i, y, true);
            // Vertical transition
            if (i > 0) {
                bool prev_high = (((i - 1 + wave_tick) % period) < (period / 2));
                if (prev_high) draw_vline(x + i, y - amplitude, amplitude + 1);
            }
        }
    }
}

// Small IR LED blaster icon
static void draw_ir_led_icon(uint8_t x, uint8_t y, bool sending) {
    // LED body — small rectangle
    draw_rect_outline(x, y + 2, 6, 8);

    // Emission arcs (3 arcs radiating right)
    for (uint8_t a = 0; a < 3; a++) {
        uint8_t offset = a * 3;
        uint8_t arc_h  = 4 + a * 2;
        uint8_t arc_x  = x + 6 + offset;
        uint8_t arc_y  = y + 6 - arc_h / 2;

        if (!sending && a > 0) continue;  // show only one arc when idle

        draw_vline(arc_x, arc_y, arc_h);
        // Slight bend effect — add pixel above/below start
        draw_pixel(arc_x + 1, arc_y + 1,        true);
        draw_pixel(arc_x + 1, arc_y + arc_h - 2, true);
    }
}

void screen_ir(GuiState *s) {
    draw_status_bar(s);
    IRContext *ir = &s->ir;
    bool sending  = (ir->state == IR_SENDING);

    // Auto-clear send state after a few ticks
    if (sending && (ir->wave_tick % 30 == 0))
        ir->state = IR_IDLE;

    // ── Header ────────────────────────────────────────────────────────────
    draw_fill_rect(0, 9, 128, 8, true);
    ssd1306_display_text(&dev, 1, "IR BLASTER", 10, false);
    ssd1306_display_text(&dev, 1, "      38KHZ", 11, false);

    // ── Separator ─────────────────────────────────────────────────────────
    draw_hline(0, 17, 128);

    // ── Command list ──────────────────────────────────────────────────────
    uint8_t start = 0;
    if (ir->selected_item >= 2) start = ir->selected_item - 1;
    if (start + IR_VISIBLE > IR_ITEM_COUNT) start = IR_ITEM_COUNT - IR_VISIBLE;

    for (uint8_t i = 0; i < IR_VISIBLE; i++) {
        uint8_t idx      = start + i;
        if (idx >= IR_ITEM_COUNT) break;
        uint8_t y        = IR_LIST_Y + i * IR_ITEM_H;
        uint8_t page     = y / 8;
        bool    selected = (idx == ir->selected_item);

        if (selected) {
            draw_fill_rect(0, y - 1, 128, IR_ITEM_H, true);

            char row[22];
            snprintf(row, sizeof(row), ">%-12s%s", ir_commands[idx], ir_protocols[idx]);
            ssd1306_display_text(&dev, page, row, strlen(row), false);
        } else {
            char row[22];
            snprintf(row, sizeof(row), " %-12s%s", ir_commands[idx], ir_protocols[idx]);
            ssd1306_display_text(&dev, page, row, strlen(row), true);
        }
    }

    // ── Bottom panel ──────────────────────────────────────────────────────
    draw_hline(0, 55, 128);

    // IR LED icon
    draw_ir_led_icon(2, 56, sending);

    // Carrier wave
    draw_carrier_wave(18, 61, ir->wave_tick, sending);

    // State label
    const char *state_label = sending ? "SENDING" : "OK:SEND";
    ssd1306_display_text(&dev, 7, state_label, strlen(state_label), true);

    // When sending — animate an additional "burst" overlay
    if (sending) {
        uint8_t burst = ir->wave_tick % 16;
        for (uint8_t b = 0; b < burst; b += 2)
            draw_pixel(100 + b, 58, true);
    }
}
