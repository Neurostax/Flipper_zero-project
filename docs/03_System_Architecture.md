# Firmware Architecture

## MCU Chosen:
- Platform: ESP32-WROOM
- SDK/Toolchain: Arduino / ESP-IDF (TBD)

## Firmware Structure

Logic Flow (Simplified)

1. Boot device, init peripherals


2. Show splash screen


3. Enter main menu loop


4. On selection, route to feature module


5. Run action, return to menu



Tasks (for RTOS-style implementation)

TaskDisplay – handles UI updates

TaskInput – handles button presses

TaskFeature – runs active module logic
