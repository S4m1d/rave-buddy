#include "animation.h"
#include "draw.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/idf_additions.h"
#include "portmacro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void animation_static_frame(i2c_port_t device_num, char *path) {
  FILE *fp = fopen(path, "rb");
  if (!fp) {
    ESP_LOGE("anim", "failed to open %s", path);
    return;
  }
  uint8_t *frame_bytes = malloc(1024);
  if (!frame_bytes) {
    ESP_LOGE("anim", "malloc failed");
    fclose(fp);
    return;
  }
  fread(frame_bytes, 1, 1024, fp);
  fclose(fp);
  draw_frame(device_num, frame_bytes);
  free(frame_bytes);
}

void animation_play(i2c_port_t device_num, char *path, int iter_count) {
  FILE *fp = fopen(path, "rb");
  if (!fp) {
    ESP_LOGE("animation_play", "failed to open %s", path);
    return;
  }

  // calculate frame count from file size
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  int frame_size = sizeof(int) + 1024;
  int frames_count = file_size / frame_size;
  ESP_LOGI("animation_play", "file size: %ld, frames count: %d", file_size,
           frames_count);

  TickType_t ticks_start = xTaskGetTickCount();
  for (int i = 0; i < iter_count; i++) {
    fseek(fp, 4, SEEK_SET);
    for (int j = 0; j < frames_count; j++) {
      int duration;
      fread(&duration, sizeof(int), 1, fp);

      uint8_t *frame_bytes = malloc(1024);
      if (!frame_bytes) {
        ESP_LOGE("animation_play", "malloc failed");
        fclose(fp);
        return;
      }

      fread(frame_bytes, 1, 1024, fp);

      draw_frame(device_num, frame_bytes);
      free(frame_bytes);

      TickType_t elapsed = xTaskGetTickCount() - ticks_start;
      TickType_t delay = pdMS_TO_TICKS(duration);

      if (elapsed < delay) {
        vTaskDelay(delay - elapsed);
      }

      ticks_start = xTaskGetTickCount();
    }
  }

  fclose(fp);
}
