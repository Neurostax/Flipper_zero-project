# Flipper Clone Development Strategy

Building a complex, multi-radio RTOS project like a Flipper Zero clone requires extreme discipline to avoid getting overwhelmed by hardware and software bugs simultaneously. This document outlines the core methodology for this project.

## 1. The "Empty Shell" First
Before a single radio module (NFC, IR, SubGHz) is connected or coded, the device must function perfectly as an "Empty Shell".
*   **What this means:** The ESP32 should boot, initialize the OLED, and allow the user to navigate a multi-level dummy menu using the physical buttons. 
*   **Why:** If the UI freezes when you press a button, you need to know it's a UI core bug, not a radio interrupt bug. The shell must be flawlessly stable first.

## 2. Hardware Abstraction Layer (HAL)
The UI and App logic must *never* talk to hardware directly. 
*   Instead of calling `Wire.write()` inside the NFC menu, the NFC menu calls `nfc.readTag()`. The `nfc_rfid.cpp` file acts as the HAL. This allows us to swap the physical NFC chip later without rewriting the UI.

## 3. The Sandbox Testing Methodology (One Radio at a Time)
Do not attempt to integrate a new module (e.g., Sub-GHz) directly into the main Flipper menu loop on day one.
*   **Isolated Testing:** Use the `RUN_SANDBOX_TEST` flag in `config.h`. Write a standalone, isolated test loop that proves the ESP32 can talk to that specific module. 
*   **Incremental Integration:** Only once the module works flawlessly in the sandbox, do you wrap it in the `BaseApp` class and add it to the `MainMenuApp`.

## 4. Dual-Core Asynchronous RTOS
The ESP32 is dual-core. To replicate the snappy feel of a real Flipper Zero, we must use FreeRTOS:
*   **Core 1 (App/UI Task):** Solely responsible for rendering the OLED and parsing button inputs. The UI never freezes.
*   **Core 0 (System/Radio Task):** Responsible for intensive background looping, such as polling 433MHz frequencies or maintaining a BLE connection.
