#include "draw.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "procedure_animation.h"
#include "ssd1306.h"
#include <string.h>

void app_main(void) {
  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  while (1) {
    procedure_animation_half_fill_spin(200, 1);
    procedure_animation_v_line_sequence(200, 2);
    procedure_animation_h_line_sequence(200, 2);
    procedure_animation_nested_rectangles(500, 1);
  }
}
