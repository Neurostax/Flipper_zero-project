#include "gui.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <string.h>

// ─────────────────────────────────────────────────────────────────────────────
//  HARDWARE CONFIG — adjust to your wiring
// ─────────────────────────────────────────────────────────────────────────────

#define I2C_SDA_PIN      21
#define I2C_SCL_PIN      22
#define I2C_FREQ_HZ      400000
#define SSD1306_ADDR     0x3C    // 0x3D if SA0 is HIGH

// Button GPIOs — input only pins (34–39) are ideal
#define BTN_UP_GPIO      34
#define BTN_DOWN_GPIO    35
#define BTN_OK_GPIO      32
#define BTN_BACK_GPIO    33
#define BTN_LEFT_GPIO    25
#define BTN_RIGHT_GPIO   26

// Debounce period in ms
#define DEBOUNCE_MS      80

// ─────────────────────────────────────────────────────────────────────────────
//  GLOBAL DISPLAY HANDLE  (declared extern in gui.h)
// ─────────────────────────────────────────────────────────────────────────────

SSD1306_t dev;

static const char *TAG = "FLIPX1";

// ─────────────────────────────────────────────────────────────────────────────
//  DISPLAY INIT
// ─────────────────────────────────────────────────────────────────────────────

void display_init(void) {
    i2c_config_t conf = {
        .mode             = I2C_MODE_MASTER,
        .sda_io_num       = I2C_SDA_PIN,
        .scl_io_num       = I2C_SCL_PIN,
        .sda_pullup_en    = GPIO_PULLUP_ENABLE,
        .scl_pullup_en    = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_FREQ_HZ,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));

    ssd1306_init(&dev, 128, 64, I2C_NUM_0, SSD1306_ADDR);
    ssd1306_clear_screen(&dev, false);
    ssd1306_contrast(&dev, 200);

    ESP_LOGI(TAG, "SSD1306 initialised at 0x%02X", SSD1306_ADDR);
}

// ─────────────────────────────────────────────────────────────────────────────
//  BUTTON INIT
// ─────────────────────────────────────────────────────────────────────────────

void buttons_init(void) {
    uint64_t pin_mask = (1ULL << BTN_UP_GPIO)    |
                        (1ULL << BTN_DOWN_GPIO)   |
                        (1ULL << BTN_OK_GPIO)     |
                        (1ULL << BTN_BACK_GPIO)   |
                        (1ULL << BTN_LEFT_GPIO)   |
                        (1ULL << BTN_RIGHT_GPIO);

    gpio_config_t io = {
        .pin_bit_mask = pin_mask,
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,  // active-LOW buttons
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io));
}

// ─────────────────────────────────────────────────────────────────────────────
//  BUTTON POLLING WITH DEBOUNCE
// ─────────────────────────────────────────────────────────────────────────────

static ButtonEvent poll_buttons(void) {
    // Active LOW — buttons pull GPIO to GND when pressed
    if (!gpio_get_level(BTN_UP_GPIO))    return BTN_UP;
    if (!gpio_get_level(BTN_DOWN_GPIO))  return BTN_DOWN;
    if (!gpio_get_level(BTN_LEFT_GPIO))  return BTN_LEFT;
    if (!gpio_get_level(BTN_RIGHT_GPIO)) return BTN_RIGHT;
    if (!gpio_get_level(BTN_OK_GPIO))    return BTN_OK;
    if (!gpio_get_level(BTN_BACK_GPIO))  return BTN_BACK;
    return BTN_NONE;
}

// ─────────────────────────────────────────────────────────────────────────────
//  OPTIONAL: Provide real RTC values to the status bar
//  Replace with your RTC driver calls if you have an RTC module.
// ─────────────────────────────────────────────────────────────────────────────

#include "esp_timer.h"

uint8_t app_rtc_hour(void) {
    return (uint8_t)((esp_timer_get_time() / 3600000000ULL) % 24);
}

uint8_t app_rtc_minute(void) {
    return (uint8_t)((esp_timer_get_time() / 60000000ULL) % 60);
}

uint8_t app_battery_level(void) {
    // Replace with real ADC battery read on your hardware
    return 75;
}

// ─────────────────────────────────────────────────────────────────────────────
//  MAIN GUI TASK
// ─────────────────────────────────────────────────────────────────────────────

void gui_task(void *arg) {
    GuiState  gui;
    gui_init(&gui);

    ButtonEvent last_btn     = BTN_NONE;
    TickType_t  last_press_t = 0;

    ESP_LOGI(TAG, "GUI task running");

    while (1) {
        ButtonEvent btn = poll_buttons();
        TickType_t  now = xTaskGetTickCount();

        // Edge detection + debounce
        if (btn != BTN_NONE &&
            btn != last_btn &&
            (now - last_press_t) > pdMS_TO_TICKS(DEBOUNCE_MS)) {

            gui_input(&gui, btn);
            last_press_t = now;
        }

        if (btn == BTN_NONE) last_btn = BTN_NONE;
        else                 last_btn = btn;

        gui_render(&gui);

        // ~30fps — gives the display plenty of I2C time at 400kHz
        vTaskDelay(pdMS_TO_TICKS(33));
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  APP ENTRY POINT (REMOVED - HANDLED BY ARDUINO SETUP)
// ─────────────────────────────────────────────────────────────────────────────

/* void app_main(void) { ... } */
