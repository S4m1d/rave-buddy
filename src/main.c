#include "animation.h"
#include "draw.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_littlefs.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "procedure_animation.h"
#include "ssd1306.h"
#include <string.h>

void app_main(void) {
  esp_vfs_littlefs_conf_t conf = {
      .base_path = "/littlefs",
      .partition_label = "spiffs", // matches partitions.csv
      .format_if_mount_failed = true,
  };
  esp_err_t ret = esp_vfs_littlefs_register(&conf);
  if (ret != ESP_OK) {
    ESP_LOGE("main", "failed to mount littlefs: %s", esp_err_to_name(ret));
    return;
  }

  i2c_init();
  ssd1306_init();
  draw_fill(0x00); // all pixels off

  while (1) {
    animation_static("/littlefs/frame.bin");
    vTaskDelay(pdMS_TO_TICKS(2000));
    draw_fill(0x00);
    procedure_animation_nested_rectangles(500, 1);
  }
}
