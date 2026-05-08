#ifndef DRAW_H
#define DRAW_H
#include "esp_err.h"

void draw_fill(uint8_t pattern);

void draw_fill_half_upper(uint8_t pattern);

void draw_fill_half_lower(uint8_t pattern);

void draw_fill_half_left(uint8_t pattern);

void draw_fill_half_right(uint8_t pattern);

esp_err_t draw_line_h(uint8_t screen_state[128][8], uint8_t start_x,
                      uint8_t start_y, uint8_t len);

esp_err_t draw_line_v(uint8_t screen_state[128][8], uint8_t start_x,
                      uint8_t start_y, uint8_t len);

esp_err_t draw_rectangle(uint8_t screen_state[128][8], uint8_t start_x,
                         uint8_t start_y, uint8_t len_x, uint8_t len_y);
#endif
