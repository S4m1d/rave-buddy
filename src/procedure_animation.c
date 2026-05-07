#include "draw.h"
#include "procedure_animation.h"
#include "driver/i2c.h"

void procedure_animation_half_fill_spin(uint64_t refresh_rate_ms) {
  while (1) {
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

void procedure_animation_h_line_sequence(uint64_t refresh_rate_ms) {
  while (1) {
    draw_line_h(10, 6, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 14, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 22, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 30, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 38, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 46, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 54, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_line_h(10, 62, 108);
    vTaskDelay(pdMS_TO_TICKS(refresh_rate_ms));

    draw_fill(0x00);
  }
}
