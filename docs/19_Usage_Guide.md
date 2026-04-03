# Usage Guide

This guide walks through how to interact with your Flipper-style device using the menu UI and buttons.

---

## Controls
- **Button A** – Navigate up
- **Button B** – Navigate down
- **Button C** – Select / Confirm

## Boot & Menu
1. On power-up, the splash screen is shown
2. Main menu appears with options:
   - IR Tools
   - NFC
   - GPIO
   - Sub-GHz
   - USB HID

Use Button A/B to scroll and Button C to select.

---

## Example: IR Tool
1. Select "IR Tools"
2. Options:
   - Record Signal
   - Transmit Last
3. Point remote at IR receiver, press "Record"
4. Use "Transmit" to replay the captured signal

---

## Example: NFC Tool
1. Select "NFC"
2. Options:
   - Read Card
   - Write Data
3. Tap a MIFARE tag on the PN532
4. Follow on-screen prompts

---

## Notes
- All modules are being tested and integrated progressively.
- Hold Button C during boot to enter "Safe Mode" (skip peripheral init).