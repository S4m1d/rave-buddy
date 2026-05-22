#ifndef DRAW_H
#define DRAW_H
#include "esp_err.h"
#include "hal/i2c_types.h"

void draw_frame(i2c_port_t device_num, uint8_t *frame_bytes);

void draw_fill(i2c_port_t device_num, uint8_t pattern);

void draw_fill_half_upper(i2c_port_t device_num, uint8_t pattern);

void draw_fill_half_lower(i2c_port_t device_num, uint8_t pattern);

void draw_fill_half_left(i2c_port_t device_num, uint8_t pattern);

void draw_fill_half_right(i2c_port_t device_num, uint8_t pattern);

esp_err_t draw_line_h(i2c_port_t device_num, uint8_t screen_state[128][8],
                      uint8_t start_x, uint8_t start_y, uint8_t len);

esp_err_t draw_line_v(i2c_port_t device_num, uint8_t screen_state[128][8],
                      uint8_t start_x, uint8_t start_y, uint8_t len);

esp_err_t draw_rectangle(i2c_port_t device_num, uint8_t screen_state[128][8],
                         uint8_t start_x, uint8_t start_y, uint8_t len_x,
                         uint8_t len_y);
#endif
