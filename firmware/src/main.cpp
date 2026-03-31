#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "config.h" // Sandbox config
#include "gpio_control.h"
#include "ui_display.h"
#include "app_framework.h"

// Instantiate core HAL
UIDisplay display;
GPIOControl gpio;
MainMenuApp menuApp;
BaseApp* activeApp = &menuApp;

// RTOS Task Handles
TaskHandle_t TaskAppCoreHandle;
TaskHandle_t TaskRadioCoreHandle;

// Core 1 Task: Handles UI rendering and App event loop
void TaskAppCore(void *pvParameters) {
    for (;;) {
        if (RUN_SANDBOX_TEST) {
            // Sandbox isolated logic runs here instead of the App Framework
            if (TEST_MODULE_DISPLAY) {
                display.showText("Sandbox: OLED Test Mode");
            }
        } 
        else if (activeApp) {
            activeApp->tick(); // Polls buttons and computes layout
        }
        
        display.update(); // Flushes buffer to OLED
        vTaskDelay(pdMS_TO_TICKS(33)); // ~30FPS refresh rate prevents CPU hogging
    }
}

// Core 0 Task: Handles background scanning (Radios)
void TaskRadioCore(void *pvParameters) {
    for (;;) {
        // Poll Sub-GHz, NFC, and BLE here silently
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize Hardware Abstraction Layers
    gpio.initialize();
    display.initialize();

    // Start App Ecosystem
    activeApp->start();

    // Spawn Core 1 Task (UI & Apps)
    xTaskCreatePinnedToCore(
        TaskAppCore, "TaskApp", 4096, NULL, 1, &TaskAppCoreHandle, 1);

    // Spawn Core 0 Task (System & Radios)
    xTaskCreatePinnedToCore(
        TaskRadioCore, "TaskRadio", 4096, NULL, 1, &TaskRadioCoreHandle, 0);
}

void loop() {
    // In FreeRTOS, the loop() is just another task (running on Core 1).
    // We leave this empty because TaskAppCore and TaskRadioCore handle everything.
    vTaskDelete(NULL); 
}