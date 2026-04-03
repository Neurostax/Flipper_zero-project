#include "ssd1306.h"
#include <string.h>
#include "esp_log.h"

#define TAG "SSD1306"

static esp_err_t i2c_write_byte(i2c_port_t i2c_num, uint8_t addr, uint8_t control_byte, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, control_byte, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

void ssd1306_init(SSD1306_t *dev, int width, int height, i2c_port_t i2c_port, int address) {
    dev->_width = width;
    dev->_height = height;
    dev->_i2c_port = i2c_port;
    dev->_address = address;
    dev->_flip = false;
    memset(dev->_buffer, 0, 1024);

    uint8_t init_cmds[] = {
        OLED_CMD_DISPLAY_OFF,
        0x20, 0x00, // Set Memory Addressing Mode (Horizontal)
        0xB0,       // Set Page Start Address
        0xC8,       // Set COM Output Scan Direction
        0x00,       // Set Low Column Address
        0x10,       // Set High Column Address
        0x40,       // Set Display Start Line
        OLED_CMD_SET_CONTRAST, 0x7F,
        0xA1,       // Set Segment Re-map
        OLED_CMD_DISPLAY_NORMAL,
        0xA8, 0x3F, // Set Multiplex Ratio
        0xAD, 0x8B, // Set DC-DC enable
        0xD3, 0x00, // Set Display Offset
        0xD5, 0x80, // Set Display Clock Divide Ratio
        0xD9, 0x22, // Set Pre-charge Period
        0xDA, 0x12, // Set COM Pins Hardware Configuration
        0xDB, 0x20, // Set VCOMH Deselect Level
        OLED_CMD_DISPLAY_RAM,
        OLED_CMD_DISPLAY_ON
    };

    for (int i = 0; i < sizeof(init_cmds); i++) {
        i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, init_cmds[i]);
    }
}

void ssd1306_clear_screen(SSD1306_t *dev, bool invert) {
    memset(dev->_buffer, invert ? 0xFF : 0, 1024);
    ssd1306_show_buffer(dev);
}

void ssd1306_contrast(SSD1306_t *dev, int contrast) {
    i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, OLED_CMD_SET_CONTRAST);
    i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, contrast);
}

void ssd1306_set_pixel(SSD1306_t *dev, int x, int y, bool color) {
    if (x < 0 || x >= dev->_width || y < 0 || y >= dev->_height) return;
    
    int index = x + (y / 8) * dev->_width;
    if (color) {
        dev->_buffer[index] |= (1 << (y % 8));
    } else {
        dev->_buffer[index] &= ~(1 << (y % 8));
    }
}

void ssd1306_show_buffer(SSD1306_t *dev) {
    for (int page = 0; page < 8; page++) {
        i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, 0xB0 + page);
        i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, 0x00);
        i2c_write_byte(dev->_i2c_port, dev->_address, OLED_CONTROL_BYTE_CMD_STREAM, 0x10);

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (dev->_address << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, OLED_CONTROL_BYTE_DATA_STREAM, true);
        i2c_master_write(cmd, &dev->_buffer[page * dev->_width], dev->_width, true);
        i2c_master_stop(cmd);
        i2c_master_cmd_begin(dev->_i2c_port, cmd, 1000 / portTICK_PERIOD_MS);
        i2c_cmd_link_delete(cmd);
    }
}

// Simple 8x8 font helper (ASCII 32-127) - placeholder for basic text
// In real nopnop2002 driver this would be more complex.
void ssd1306_display_text(SSD1306_t *dev, int page, const char *text, int len, bool invert) {
    // This is a simplified wrapper. The native gui.c calls this.
    // For now, we'll just log it or draw placeholders. 
    // Ideally we'd use a font table here.
    ESP_LOGI(TAG, "Display Text at page %d: %s", page, text);
    // Real implementation would draw characters into dev->_buffer
    // For the sake of this task, we will assume gui.c primitives work.
    ssd1306_show_buffer(dev); 
}
