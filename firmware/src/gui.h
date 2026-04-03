#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "ssd1306.h"

// ─────────────────────────────────────────────
//  Display handle (defined in display.c)
// ─────────────────────────────────────────────
extern SSD1306_t dev;

// ─────────────────────────────────────────────
//  Screen IDs
// ─────────────────────────────────────────────
typedef enum {
    SCREEN_MENU = 0,
    SCREEN_RF_TOOLS,
    SCREEN_NFC,
    SCREEN_IR,
    SCREEN_GPIO,
    SCREEN_SETTINGS,
    SCREEN_COUNT
} ScreenID;

// ─────────────────────────────────────────────
//  Button events
// ─────────────────────────────────────────────
typedef enum {
    BTN_NONE = 0,
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_OK,
    BTN_BACK
} ButtonEvent;

// ─────────────────────────────────────────────
//  RF Tools sub-state
// ─────────────────────────────────────────────
typedef enum {
    RF_IDLE = 0,
    RF_SCANNING,
    RF_RECORDING,
    RF_ANALYZING
} RFState;

typedef struct {
    uint8_t  selected_item;       // highlighted menu item
    RFState  state;
    float    frequency_mhz;       // e.g. 433.92
    uint8_t  signal_strength;     // 0–100
    bool     recording;
    uint8_t  bar_anim;            // animation tick for signal bars
} RFContext;

// ─────────────────────────────────────────────
//  NFC sub-state
// ─────────────────────────────────────────────
typedef enum {
    NFC_IDLE = 0,
    NFC_SCANNING,
    NFC_FOUND,
    NFC_READ_OK,
    NFC_ERROR
} NFCState;

typedef struct {
    NFCState state;
    char     uid[16];             // last scanned UID string  "3A:BC:FE:21"
    char     card_type[12];       // "Mifare 1K", "NTAG213" …
    uint8_t  pulse_tick;          // animation tick for ring
} NFCContext;

// ─────────────────────────────────────────────
//  IR Blaster sub-state
// ─────────────────────────────────────────────
typedef enum {
    IR_IDLE = 0,
    IR_SENDING,
    IR_LEARNING,
    IR_SAVED
} IRState;

typedef struct {
    uint8_t  selected_item;
    IRState  state;
    uint8_t  wave_tick;           // carrier wave animation
} IRContext;

// ─────────────────────────────────────────────
//  GPIO Monitor sub-state
// ─────────────────────────────────────────────
#define GUI_GPIO_PIN_COUNT 5

typedef enum {
    PIN_MODE_IN = 0,
    PIN_MODE_OUT,
    PIN_MODE_PWM
} PinMode;

typedef struct {
    const char *name;
    PinMode     mode;
    uint8_t     value;            // 0/1 for digital, 0–100 for PWM %
} GPIOPin;

typedef struct {
    GPIOPin pins[GUI_GPIO_PIN_COUNT];
    uint8_t selected_pin;
    uint8_t pwm_tick;             // animation tick
} GPIOContext;

// ─────────────────────────────────────────────
//  Settings sub-state
// ─────────────────────────────────────────────
#define SETTINGS_ITEM_COUNT 4

typedef struct {
    uint8_t selected_item;
    uint8_t brightness;           // 0–255
    bool    flip_display;
    char    device_name[16];
} SettingsContext;

// ─────────────────────────────────────────────
//  Top-level GUI state
// ─────────────────────────────────────────────
typedef struct {
    ScreenID        current;
    uint8_t         menu_index;
    uint32_t        tick;         // global animation counter

    // Per-screen contexts
    RFContext       rf;
    NFCContext      nfc;
    IRContext       ir;
    GPIOContext     gpio;
    SettingsContext settings;
} GuiState;

// ─────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────
void gui_init(GuiState *state);
void gui_render(GuiState *state);
void gui_input(GuiState *state, ButtonEvent btn);

// Individual screen renderers (also usable standalone)
void screen_menu(GuiState *s);
void screen_rf(GuiState *s);
void screen_nfc(GuiState *s);
void screen_ir(GuiState *s);
void screen_gpio(GuiState *s);
void screen_settings(GuiState *s);

// Shared drawing helpers
void draw_status_bar(GuiState *s);
void draw_hline(uint8_t x, uint8_t y, uint8_t len);
void draw_vline(uint8_t x, uint8_t y, uint8_t len);
void draw_rect_outline(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void draw_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
void draw_pixel(uint8_t x, uint8_t y, bool color);
void draw_text_page(uint8_t page, uint8_t x_px, const char *text, bool invert);
void draw_signal_bars(uint8_t x, uint8_t y, uint8_t strength);
void draw_battery_icon(uint8_t x, uint8_t y, uint8_t level);
