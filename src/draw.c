#include "draw.h"
#include "driver/i2c.h"
#include "hal/i2c_types.h"
#include "ssd1306.h"

void draw_fill(uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_upper(uint8_t pattern) {
  for (uint8_t page = 0; page <= 3; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_lower(uint8_t pattern) {
  for (uint8_t page = 4; page < 8; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_left(uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(page);
    ssd1306_cmd_set_col(0);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 64; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_right(uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(page);
    ssd1306_cmd_set_col(0x40);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true);
    for (uint8_t i = 64; i < 128; i++) { // only right 64 columns
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

esp_err_t draw_line_h(uint8_t start_x, uint8_t start_y, uint8_t len) {
  if (start_y >= 64 || start_x >= 128 || len > 128) {
    return ESP_ERR_INVALID_SIZE;
  }
  if (start_x + len > 128) {
    return ERR_LINE_OUT_OF_SCREEN;
  }

  uint8_t start_page = start_y / 8;
  ssd1306_cmd_set_page(start_page);
  ssd1306_cmd_set_col(start_x);

  i2c_cmd_handle_t handle = i2c_cmd_link_create();
  i2c_master_start(handle);
  ssd1306_set_as_i2c_device(handle, I2C_MASTER_WRITE);
  ssd1306_set_mode(handle, Data);

  for (int i = 0; i < len; i++) {
    ssd1306_write_page(handle, 0x01 << (start_y%8));
  }

  i2c_master_stop(handle);
  i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));// actually send previously written bytes sequence from buffer to i2c
  i2c_cmd_link_delete(handle);

  return ESP_OK;
}
