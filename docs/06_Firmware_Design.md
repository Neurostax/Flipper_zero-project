# Firmware Design

## Architecture
- Modular source tree per feature (IR, NFC, etc.)
- Central menu system
- Hardware abstraction layer

## State Machines
- Boot → Menu → Feature Modules → Exit/Return

## Peripherals Used
- I2C: OLED, NFC
- SPI: MicroSD
- GPIO: Buttons, IR
- UART (optional): Debug

## Libraries
- Adafruit_SSD1306
- PN532 NFC
- IRremote