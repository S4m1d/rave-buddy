#ifndef SSD1306_H
#define SSD1306_H

#include "esp_err.h"

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_FREQ_HZ 400000
#define I2C_MASTER_NUM I2C_NUM_0
#define SSD1306_ADDR 0x3C

#define ERR_LINE_OUT_OF_SCREEN (ESP_ERR_INVALID_STATE);

void i2c_init(void);

void ssd1306_cmd(uint8_t cmd);
void ssd1306_init(void);
void ssd1306_cmd_set_page(uint8_t page);
void ssd1306_cmd_set_col(uint8_t col);

#endif
