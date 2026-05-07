#include "draw.h"
#include "ssd1306.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

void app_main(void) {
  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  while (1) {
    draw_fill_half_left(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    draw_fill_half_left(0x00); // all pixels off

    draw_fill_half_upper(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    draw_fill_half_upper(0x00); // all pixels off

    draw_fill_half_right(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    draw_fill_half_right(0x00); // all pixels off

    draw_fill_half_lower(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    draw_fill_half_lower(0x00); // all pixels off
  }
}
