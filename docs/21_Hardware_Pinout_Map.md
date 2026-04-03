# Hardware Pin Mapping

This document provides a 1:1 hardware mapping table for connecting the core ESP32-WROOM pins to the various Flipper modules.

| Module         | Function           | ESP32 Pin   | Notes                         |
|----------------|--------------------|-------------|-------------------------------|
| OLED Display   | I2C SCL            | D22         | Standard I2C                  |
| OLED Display   | I2C SDA            | D21         | Standard I2C                  |
| IR Receiver    | Digital IN         | D27         | Reallocated (was D33)         |
| IR LED         | PWM Output         | D13         | Reallocated (was D25)         |
| PN532 NFC      | SPI CS             | D5          |                               |
| Sub-GHz TX     | SPI MOSI           | D23         |                               |
| Button UP      | Input Pull-up      | D34         | Navigation                    |
| Button DOWN    | Input Pull-up      | D35         | Navigation                    |
| Button LEFT    | Input Pull-up      | D25         | Navigation                    |
| Button RIGHT   | Input Pull-up      | D26         | Navigation                    |
| Button OK      | Input Pull-up      | D32         | Select/Enter                  |
| Button BACK    | Input Pull-up      | D33         | Back/Cancel                   |
| 1-Wire         | iButton IN         | TBD         |                               |
| 125kHz RFID    | SPI/I2C/UART       | TBD         |                               |
| Buzzer         | PWM OUT            | TBD         | Needs reallocation (was D27)  |
| RGB LED        | PWM RGB            | TBD         | Needs reallocation (was D13)  |

*Note: Pins marked TBD need to be assigned based on the final PCB routing in the Kicad files.*
