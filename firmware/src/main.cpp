#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "config.h"
#include "gpio_control.h"
#include "ir_control.h"

// Bridge to native C GUI
extern "C" {
    #include "gui.h"
    #include "ssd1306.h"
    
    // Forward declarations for functions from the moved main.c logic
    void display_init(void);
    void buttons_init(void);
    void gui_task(void *arg);
}

// Global instances
IRControl ir;
GPIOControl gpio;

// Task Handles
TaskHandle_t TaskGuiHandle;
TaskHandle_t TaskRadioCoreHandle;

// Core 0 Task: Handles background scanning (Radios)
void TaskRadioCore(void *pvParameters) {
    for (;;) {
        // Poll Sub-GHz, NFC, and BLE here silently
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize Hardware
    ir.initialize();
    
    // Initialize Native C Display & Buttons
    display_init();
    buttons_init();

    // Show Splash Screen (using native driver)
    ssd1306_display_text(&dev, 2, "   FLIP-X1", 10, false);
    ssd1306_display_text(&dev, 4, " BOOTING...", 11, false);
    delay(1500);

    // Spawn GUI Task on Core 1
    xTaskCreatePinnedToCore(
        gui_task, "GuiTask", 4096, NULL, 5, &TaskGuiHandle, 1);

    // Spawn Background Radio Task on Core 0
    xTaskCreatePinnedToCore(
        TaskRadioCore, "RadioTask", 4096, NULL, 1, &TaskRadioCoreHandle, 0);
}

void loop() {
    // Arduino loop remains empty as FreeRTOS tasks handle everything
    vTaskDelete(NULL); 
}