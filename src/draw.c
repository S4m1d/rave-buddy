#include "draw.h"
#include "driver/i2c.h"
#include "freertos/projdefs.h"
#include "hal/i2c_types.h"
#include "ssd1306.h"
#include <stdint.h>

void draw_frame(i2c_port_t device_num, uint8_t *frame_bytes) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(device_num, page);
    ssd1306_cmd_set_col(device_num, 0);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    ssd1306_set_as_i2c_device(handle, I2C_MASTER_WRITE);
    ssd1306_set_mode(handle, Data);
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, frame_bytes[page * 128 + i], true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill(i2c_port_t device_num, uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(device_num, page);
    ssd1306_cmd_set_col(device_num, 0);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    ssd1306_set_as_i2c_device(handle, I2C_MASTER_WRITE);
    ssd1306_set_mode(handle, Data);
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_upper(i2c_port_t device_num, uint8_t pattern) {
  for (uint8_t page = 0; page <= 3; page++) {
    ssd1306_cmd(device_num, 0xB0 + page);
    ssd1306_cmd(device_num, 0x00);
    ssd1306_cmd(device_num, 0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_lower(i2c_port_t device_num, uint8_t pattern) {
  for (uint8_t page = 4; page < 8; page++) {
    ssd1306_cmd(device_num, 0xB0 + page);
    ssd1306_cmd(device_num, 0x00);
    ssd1306_cmd(device_num, 0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_left(i2c_port_t device_num, uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(device_num, page);
    ssd1306_cmd_set_col(device_num, 0);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 64; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

void draw_fill_half_right(i2c_port_t device_num, uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd_set_page(device_num, page);
    ssd1306_cmd_set_col(device_num, 0x40);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true);
    for (uint8_t i = 64; i < 128; i++) { // only right 64 columns
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_DISPLAY_1, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

esp_err_t draw_line_h(i2c_port_t device_num, uint8_t screen_state[128][8],
                      uint8_t start_x, uint8_t start_y, uint8_t len) {
  if (start_y >= 64 || start_x >= 128 || len > 128) {
    return ESP_ERR_INVALID_SIZE;
  }
  if (start_x + len > 128) {
    return ERR_LINE_OUT_OF_SCREEN;
  }

  uint8_t start_page = start_y / 8;
  ssd1306_cmd_set_page(device_num, start_page);
  ssd1306_cmd_set_col(device_num, start_x);

  i2c_cmd_handle_t handle = i2c_cmd_link_create();
  i2c_master_start(handle);
  ssd1306_set_as_i2c_device(handle, I2C_MASTER_WRITE);
  ssd1306_set_mode(handle, Data);

  for (int i = start_x; i < start_x + len; i++) {
    uint8_t prev_val = screen_state[i][start_page];
    uint8_t new_val = (0x01 << (start_y % 8)) | prev_val;
    ssd1306_write_page(handle, new_val);
    screen_state[i][start_page] = new_val;
  }

  i2c_master_stop(handle);
  i2c_master_cmd_begin(I2C_DISPLAY_1, handle,
                       pdMS_TO_TICKS(100)); // actually send previously written
                                            // bytes sequence from buffer to i2c
  i2c_cmd_link_delete(handle);

  return ESP_OK;
}

esp_err_t draw_line_v(i2c_port_t device_num, uint8_t screen_state[128][8],
                      uint8_t start_x, uint8_t start_y, uint8_t len) {
  if (start_y >= 64 || start_x >= 128 || len > 128) {
    return ESP_ERR_INVALID_SIZE;
  }
  if (start_y + len > 64) {
    return ERR_LINE_OUT_OF_SCREEN;
  }

  uint8_t start_page = start_y / 8;
  uint8_t end_page = (start_y + len - 1) / 8;

  for (int i = start_page; i <= end_page; i++) {
    ssd1306_cmd_set_page(device_num, i);
    ssd1306_cmd_set_col(device_num, start_x);

    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    ssd1306_set_as_i2c_device(handle, I2C_MASTER_WRITE);
    ssd1306_set_mode(handle, Data);

    uint8_t prev_val = screen_state[start_x][i];
    uint8_t new_val;
    if (i == start_page) {
      new_val = 0xFF << (start_y % 8) | prev_val;
      ssd1306_write_page(handle, 0xFF << (start_y % 8));
    } else if (i == end_page) {
      new_val = 0xFF >> (8 - (start_y + len - 1) % 8) | prev_val;
      ssd1306_write_page(handle, new_val);
    } else {
      new_val = 0xFF;
      ssd1306_write_page(handle, new_val);
    }
    screen_state[start_x][i] = new_val;

    i2c_master_stop(handle);
    i2c_master_cmd_begin(
        I2C_DISPLAY_1, handle,
        pdMS_TO_TICKS(100)); // actually send previously written bytes sequence
                             // from buffer to i2c
    i2c_cmd_link_delete(handle);
  }
  return ESP_OK;
}

esp_err_t draw_rectangle(i2c_port_t device_num, uint8_t screen_state[128][8],
                         uint8_t start_x, uint8_t start_y, uint8_t len_x,
                         uint8_t len_y) {
  esp_err_t rc;

  rc = draw_line_h(device_num, screen_state, start_x, start_y, len_x);
  if (rc != ESP_OK) {
    return rc;
  }

  rc = draw_line_h(device_num, screen_state, start_x, start_y + len_y - 1,
                   len_x);
  if (rc != ESP_OK) {
    return rc;
  }

  rc = draw_line_v(device_num, screen_state, start_x, start_y, len_y);
  if (rc != ESP_OK) {
    return rc;
  }

  rc = draw_line_v(device_num, screen_state, start_x + len_x - 1, start_y,
                   len_y);
  if (rc != ESP_OK) {
    return rc;
  }

  return ESP_OK;
}
