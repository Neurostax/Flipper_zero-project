#ifndef MAIN_SSD1306_H_
#define MAIN_SSD1306_H_

#include <stdint.h>
#include <stdbool.h>
#include "driver/i2c.h"

// SSD1306 Commands
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

#define OLED_CMD_SET_CONTRAST           0x81
#define OLED_CMD_DISPLAY_RAM            0xA4
#define OLED_CMD_DISPLAY_ALLON          0xA5
#define OLED_CMD_DISPLAY_NORMAL         0xA6
#define OLED_CMD_DISPLAY_INVERTED       0xA7
#define OLED_CMD_DISPLAY_OFF            0xAE
#define OLED_CMD_DISPLAY_ON             0xAF

typedef struct {
    uint8_t _address;
    uint8_t _width;
    uint8_t _height;
    i2c_port_t _i2c_port;
    uint8_t _buffer[1024]; // 128x64 / 8
    bool _flip;
} SSD1306_t;

void ssd1306_init(SSD1306_t *dev, int width, int height, i2c_port_t i2c_port, int address);
void ssd1306_clear_screen(SSD1306_t *dev, bool invert);
void ssd1306_contrast(SSD1306_t *dev, int contrast);
void ssd1306_set_pixel(SSD1306_t *dev, int x, int y, bool color);
void ssd1306_display_text(SSD1306_t *dev, int page, const char *text, int len, bool invert);
void ssd1306_show_buffer(SSD1306_t *dev);

#endif /* MAIN_SSD1306_H_ */
