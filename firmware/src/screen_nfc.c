#include "gui.h"
#include <stdio.h>
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  SCREEN: NFC / RFID
//
//  Layout (128×64):
//  ┌────────────────────────────────┐
//  │ FLIP-X1      12:00   [BAT]    │  status bar
//  ├────────────────────────────────┤
//  │ NFC / RFID                    │  title
//  ├────────────────────────────────┤
//  │   [    NFC    ]  READY TO     │  icon left / status right
//  │   [  symbol   ]  SCAN CARD    │
//  │   [   pulse   ]               │
//  ├────────────────────────────────┤
//  │ TYPE: NONE                    │  card info row
//  │ UID:  --:--:--:--             │  UID row
//  └────────────────────────────────┘
// ─────────────────────────────────────────────────────────────────────────────

// NFC icon: concentric arcs representing field waves
static void draw_nfc_icon(uint8_t cx, uint8_t cy, uint8_t pulse_tick) {
    // Outer box
    draw_rect_outline(cx - 14, cy - 12, 28, 24);

    // Three arc columns — simplified as short vertical lines of varying height
    // to suggest radiating field lines
    uint8_t radii[3] = {4, 7, 10};
    for (uint8_t r = 0; r < 3; r++) {
        uint8_t h   = radii[r];
        uint8_t arc_x = cx + radii[r] - 2;
        // Fade in/out based on pulse — outer arc breathes
        bool visible = true;
        if (r == 2) {
            // Outer arc pulses on/off
            visible = (pulse_tick & 0x10) == 0;
        }
        if (visible) {
            draw_vline(arc_x, cy - h / 2, h);
        }
    }

    // Centre dot
    draw_fill_rect(cx - 1, cy - 1, 3, 3, true);

    // Pulse ring (expanding square when scanning)
    uint8_t ring_size = (pulse_tick >> 2) % 8;
    draw_rect_outline(cx - 14 - ring_size,
                      cy - 12 - ring_size,
                      28 + ring_size * 2,
                      24 + ring_size * 2);
}

// Card found icon — small card outline with checkmark
static void draw_card_found(uint8_t cx, uint8_t cy) {
    draw_rect_outline(cx - 14, cy - 10, 28, 20);
    // Chip outline
    draw_rect_outline(cx - 6, cy - 5, 12, 10);
    // Chip lines
    draw_hline(cx - 6, cy, 12);
    draw_vline(cx, cy - 5, 10);
    // Tick mark
    draw_pixel(cx + 10, cy - 7, true);
    draw_pixel(cx + 11, cy - 6, true);
    draw_pixel(cx + 12, cy - 5, true);
    draw_pixel(cx + 11, cy - 4, true);
    draw_pixel(cx + 10, cy - 3, true);
}

static const char *nfc_status_lines[][2] = {
    { "READY TO",    "SCAN CARD" },    // NFC_IDLE
    { "SCANNING",    "HOLD CARD" },    // NFC_SCANNING
    { "CARD FOUND!", "READING..." },   // NFC_FOUND
    { "READ OK",     "PRESS BACK" },   // NFC_READ_OK
    { "ERROR",       "TRY AGAIN" },    // NFC_ERROR
};

void screen_nfc(GuiState *s) {
    draw_status_bar(s);
    NFCContext *nfc = &s->nfc;

    // ── Title ─────────────────────────────────────────────────────────────
    draw_fill_rect(0, 9, 128, 8, true);
    ssd1306_display_text(&dev, 1, "NFC / RFID", 10, false);

    // ── Separator ─────────────────────────────────────────────────────────
    draw_hline(0, 17, 128);

    // ── NFC icon (left column, centred vertically in remaining space) ──────
    uint8_t icon_cx = 28;
    uint8_t icon_cy = 36;

    if (nfc->state == NFC_READ_OK || nfc->state == NFC_FOUND) {
        draw_card_found(icon_cx, icon_cy);
    } else {
        draw_nfc_icon(icon_cx, icon_cy, nfc->pulse_tick);
    }

    // Vertical divider
    draw_vline(56, 17, 36);

    // ── Status text (right column) ────────────────────────────────────────
    uint8_t si = (uint8_t)nfc->state;
    if (si >= 5) si = 0;

    // Line 1
    ssd1306_display_text(&dev, 3, nfc_status_lines[si][0], strlen(nfc_status_lines[si][0]), true);
    // Line 2
    ssd1306_display_text(&dev, 4, nfc_status_lines[si][1], strlen(nfc_status_lines[si][1]), true);

    // OK button hint
    if (nfc->state == NFC_IDLE) {
        ssd1306_display_text(&dev, 5, "OK: START", 9, true);
    }

    // ── Card info panel (bottom, full width) ──────────────────────────────
    draw_hline(0, 54, 128);

    char type_row[22];
    snprintf(type_row, sizeof(type_row), "TYPE:%-8s", nfc->card_type);
    ssd1306_display_text(&dev, 7, type_row, strlen(type_row), true);

    // UID row at page 6 (y=48)
    char uid_row[22];
    snprintf(uid_row, sizeof(uid_row), "UID: %s", nfc->uid);
    ssd1306_display_text(&dev, 6, uid_row, strlen(uid_row), true);

    // Blinking cursor when scanning
    if (nfc->state == NFC_SCANNING && (nfc->pulse_tick & 0x20)) {
        draw_pixel(125, 56, true);
        draw_pixel(126, 56, true);
        draw_pixel(125, 57, true);
        draw_pixel(126, 57, true);
    }
}
