# Testing Log

Module-by-module tracking of hardware and firmware test results.

---

## Display (OLED)
- [x] SSD1306 wired via I2C
- [x] Displaying splash screen & text
- [ ] Add icons or graphics support

## Button Inputs
- [x] 3 buttons read using digitalRead()
- [x] Debounce logic tested

## IR Module
- [x] IR Receiver detects NEC protocol
- [x] IR LED transmits captured signal
- [ ] Range testing and power boost (transistor stage)

## NFC (PN532)
- [ ] Wired via SPI
- [ ] Reads MIFARE cards
- [ ] Write mode pending

## USB HID
- [ ] ESP32 HID library integrated
- [ ] Send keystrokes to PC

## GPIO Tools
- [ ] Pin mode selector (input/output)
- [ ] Simple toggling verified

## Sub-GHz (CC1101)
- [ ] Module received
- [ ] SPI communication working
- [ ] Basic transmission tested