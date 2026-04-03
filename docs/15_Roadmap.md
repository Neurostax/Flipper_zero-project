# Project Roadmap: Flipper Zero Clone

This roadmap outlines the phased development plan for the custom Flipper Zero clone. Each phase builds upon the previous one to ensure consistent progress, testing, and integration of features.

---

## 📍 Phase 1: Foundation Setup (Week 1)
> Goal: Establish development environment and basic functionality

- [ ] Set up Git repository and documentation structure
- [ ] Initialize PlatformIO/Arduino project
- [ ] Set up OLED display (test text & menu rendering)
- [ ] Implement input handler for physical buttons
- [ ] Create basic menu navigation system

---

## 📍 Phase 2: Module Prototyping (Weeks 2–3)
> Goal: Integrate core modules and verify hardware functionality

- [ ] **IR Transceiver**
  - [ ] Receive NEC codes
  - [ ] Transmit saved codes

- [ ] **NFC (PN532) & 125kHz RFID**
  - [ ] Detect NFC tags & Read MIFARE UID
  - [ ] Read/Emulate 125kHz low-frequency tags

- [ ] **Sub-GHz RF Module**
  - [ ] Capture raw signals
  - [ ] Replay signals (basic)
  
- [ ] **iButton (1-Wire)**
  - [ ] Read generic iButton keys
  - [ ] Save to storage

---

## 📍 Phase 3: UI/UX & Storage Integration (Weeks 4–5)
> Goal: Enhance interaction experience and implement storage

- [ ] Refactor menu with scrolling & icons
- [ ] Save IR/NFC/RF data to SD card (SPI interface)
- [ ] File manager for viewing & selecting stored signals
- [ ] Add settings menu (e.g., brightness, timeout)

---

## 📍 Phase 4: USB Tools & Expansion (Week 6)
> Goal: Add USB HID emulation and prepare for extension

- [ ] Implement USB HID keyboard/mouse (ESP32 native USB or USB host shield)
- [ ] Add GPIO tool: simple HIGH/LOW toggle
- [ ] Power consumption optimization (sleep mode, LED usage)
- [ ] **Bluetooth LE**: Smartphone pairing and app sync
- [ ] **U2F Security Token**: FIDO U2F emulation over USB/BLE

---

## 📍 Phase 5: Final Polish & Packaging (Weeks 7–8)
> Goal: Finalize system for daily use and public release

- [ ] Create icon-based UI (visual polish)
- [ ] Add firmware updater support (OTA or USB)
- [ ] Hardware enclosure design (3D printed or CNC)
- [ ] Conduct full integration test
- [ ] Prepare v1.0 release notes & user manual

---

## ✅ Future Ideas / Stretch Goals
- Custom scripting language for signals
- WiFi sniffing or signal analyzer
- GPS tracker module support
- Cloud sync of saved profiles
- Expand Sub-GHz support to 433 MHz garage remotes

---

## 🔁 Progress Tracking
Use `changelog.md` to document detailed feature additions and bug fixes.
Use `testing_log.md` to track module validation.

---

## 🎯 Final Goal
An offline, handheld, multi-tool gadget replicating and expanding Flipper Zero functionalities tailored to personal experiments, learning, and ethical hacking tasks.