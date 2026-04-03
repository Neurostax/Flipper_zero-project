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
- `docs/01_Project_Overview.md`
- `docs/03_System_Architecture.md`
- `docs/04_Bill_of_Materials.md`
- `docs/15_Roadmap.md`
- `docs/18_Interface_Design.md`
- `docs/19_Usage_Guide.md`
- `docs/21_Hardware_Pinout_Map.md`
- `docs/22_Development_Strategy.md`

## Status
> Project is in early development. Modules will be added iteratively.

