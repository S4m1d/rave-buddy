#include "animation.h"
#include "draw.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "procedure_animation.h"
#include "sd_card.h"
#include "ssd1306.h"
#include <dirent.h>
#include <string.h>

void list_sdcard() {
  DIR *dir = opendir("/sdcard");
  if (!dir) {
    ESP_LOGE("list_sdcard", "failed to open /sdcard dir");
    return;
  }
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    ESP_LOGI("list_sdcard", "found: %s", entry->d_name);
  }
  closedir(dir);
}

void app_main(void) {
  sd_card_init();
  //list_sdcard();

  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  while (1) {
//    animation_static_frame("/sdcard/frame.bin");
//    vTaskDelay(pdMS_TO_TICKS(2000));
    animation_play("/sdcard/animation.bin", 100);
//    draw_fill(0x00);
//    procedure_animation_nested_rectangles(500, 1);
  }
}
