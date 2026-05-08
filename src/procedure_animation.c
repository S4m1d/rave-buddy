#include "procedure_animation.h"
#include "draw.h"
#include "driver/i2c.h"
#include <string.h>

void procedure_animation_half_fill_spin(uint64_t refresh_rate_ms,
                                        int iter_num) {
  for (int i = 0; i < iter_num; i++) {
    draw_fill_half_left(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));
    draw_fill_half_left(0x00); // all pixels off

    draw_fill_half_upper(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));
    draw_fill_half_upper(0x00); // all pixels off

    draw_fill_half_right(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));
    draw_fill_half_right(0x00); // all pixels off

    draw_fill_half_lower(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));
    draw_fill_half_lower(0x00); // all pixels off
  }
}

void procedure_animation_h_line_sequence(uint64_t refresh_rate_ms,
                                         int iter_num) {

  uint8_t screen_state[128][8] = {0};
  for (int i = 0; i < iter_num; i++) {
    draw_line_h(screen_state, 10, 6, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 14, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 22, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 30, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 38, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 46, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 54, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(screen_state, 10, 62, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_fill(0x00);
  }
}

void procedure_animation_v_line_sequence(uint64_t refresh_rate_ms,
                                         int iter_num) {

  uint8_t screen_state[128][8] = {0};
  for (int i = 0; i < iter_num; i++) {
    draw_line_v(screen_state, 15, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 31, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 47, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 63, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 79, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 95, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 95, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 111, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_v(screen_state, 127, 5, 53);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_fill(0x00);
  }
}

void procedure_animation_nested_rectangles(uint64_t refresh_rate_ms,
                                           int iter_num) {
  for (int i = 0; i < iter_num; i++) {
    uint8_t screen_state[128][8] = {0};
    int total_offset = 24;
    for (int i = 0; i < total_offset; i += 4) {
      draw_rectangle(screen_state, 4 + i, 4 + i, 120 - i * 2, 56 - i * 2);
      vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));
      draw_fill(0x00);
      memset(screen_state, 0x00, sizeof(screen_state));
    }

    for (int i = 0; i <= total_offset; i += 4) {
      draw_rectangle(screen_state, 4 + total_offset - i, 4 + total_offset - i,
                     120 - (total_offset - i) * 2, 56 - (total_offset - i) * 2);
      vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms/2));
    }

    draw_fill(0x00);
    memset(screen_state, 0x00, sizeof(screen_state));
  }
}
