#include "draw.h"
#include "procedure_animation.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"
#include <string.h>


void app_main(void) {
  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  procedure_animation_h_line_sequence(200);
}
