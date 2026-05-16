#include "animation.h"
#include "draw.h"
#include "sd_card.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "procedure_animation.h"
#include "ssd1306.h"
#include <string.h>

void app_main(void) {
  sd_card_init();

  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  while (1) {
    animation_static("/sdcard/frame.bin");
    vTaskDelay(pdMS_TO_TICKS(2000));
    draw_fill(0x00);
    procedure_animation_nested_rectangles(500, 1);
  }
}
