# System Architecture & Firmware Design

## 📍 Hardware Architecture
- **MCU Platform**: ESP32-WROOM
- **SDK/Toolchain**: Arduino / ESP-IDF (TBD)
- **Peripherals Used**:
  - **I2C**: OLED, NFC (PN532)
  - **SPI**: MicroSD
  - **GPIO**: Buttons, IR
  - **UART (optional)**: Debug

## 🧠 Firmware Structure
- Modular source tree per feature (IR, NFC, Sub-GHz, etc.)
- Central menu system
- Hardware abstraction layer

### App Framework & OS (FAP-Style Replica)
- **Plugin Architecture**: Each tool (IR, NFC) should be a self-contained "App" module conforming to a standard interface.
- **Hardware Abstraction Layer (HAL)**: The UI and App logic must *never* talk to hardware directly. They use the HAL. This makes swapping components (e.g. PN532 vs CC1101) easy.
- **PC UI Simulation**: The UI layer and App Framework should be compiled for desktop (TDD) using a simulator, speeding up UI layout design without flashing the ESP32 repeatedly.

### Logic Flow (Simplified)
1. Boot device, init HAL peripherals
2. Launch RTOS Scheduler -> Show splash screen
3. Main Menu App discovers available tool Apps
4. Launch Tool App -> Runs event loops using HAL
5. Exit Tool App -> Return to Main Menu

### RTOS Core Utilization
Because the ESP32 is dual-core, we leverage FreeRTOS actively to prevent UI freezing:
- **Core 1 (App/UI Task):** Renders the OLED, parses button inputs, runs the active App's logic.
- **Core 0 (System/Radio Task):** Polls 433MHz frequencies, scans NFC, manages BLE/WiFi backgrounds without interrupting the screen.

## 📚 Libraries
- Adafruit_SSD1306
- PN532 NFC
- IRremote
