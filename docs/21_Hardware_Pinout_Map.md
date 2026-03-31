# Hardware Pin Mapping

This document provides a 1:1 hardware mapping table for connecting the core ESP32-WROOM pins to the various Flipper modules.

| Module         | Function           | ESP32 Pin   | Notes                         |
|----------------|--------------------|-------------|-------------------------------|
| OLED Display   | I2C SCL            | D22         | Adjustable                    |
| OLED Display   | I2C SDA            | D21         |                               |
| IR Receiver    | Digital IN         | D33         | TSOP382 compatible            |
| IR LED         | PWM Output         | D25         | Use transistor if needed      |
| PN532 NFC      | SPI CS             | D5          | Changeable if needed          |
| Sub-GHz TX     | SPI MOSI           | D23         | Via external module           |
| Button A       | Input Pull-up      | D18         | Menu select                   |
| Button B       | Input Pull-up      | D19         | Back/Cancel                   |
| Button Up      | Input Pull-up      | D4          | Menu scroll up                |
| Button Down    | Input Pull-up      | D15         | Menu scroll down              |
| Buzzer         | PWM OUT            | D27         | Optional                      |
| RGB LED        | PWM RGB            | D13/D12/D14 | Status LEDs                   |
| 1-Wire         | iButton IN         | TBD         | Needs dedicated pin           |
| 125kHz RFID    | SPI/I2C/UART       | TBD         | Pending module choice         |

*Note: Pins marked TBD need to be assigned based on the final PCB routing in the Kicad files.*
