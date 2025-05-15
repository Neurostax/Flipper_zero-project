# Custom Flipper Zero Clone

This is a personal, open-source multi-tool project inspired by Flipper Zero. It aims to combine multiple radio and input/output technologies into a single handheld, battery-powered device with a button-based interface and OLED screen.

## Features (Planned / In Progress)
- IR Receiver & Transmitter (NEC Protocol)
- Sub-GHz radio scanner/replayer (RF Module)
- NFC Reader/Writer (PN532)
- USB HID Emulation (Keyboard/Mouse)
- GPIO Tool for basic electrical testing
- MicroSD card storage
- OLED UI and menu system
- Battery-powered operation

## Hardware Platform
- **MCU**: ESP32-WROOM (Dev board or custom PCB)
- **Display**: 0.96" I2C OLED (SSD1306)
- **Modules**: IR, NFC (PN532), Sub-GHz RF, HID, etc.
- **Controls**: 3-button interface
- **Power**: Li-ion with charging circuit or USB

## Setup
1. Install [PlatformIO](https://platformio.org/) or Arduino IDE
2. Clone this repository
3. Open project in your IDE
4. Wire modules according to `hardware_pinout.md`
5. Upload `src/main.cpp` to ESP32

## Documentation
- `firmware_architecture.md`
- `hardware_pinout.md`
- `features.md`
- `usage_guide.md`
- `testing_log.md`
- `changelog.md`

## Status
> Project is in early development. Modules will be added iteratively.

