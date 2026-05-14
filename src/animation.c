#include "animation.h"
#include "draw.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void animation_static(char *path) {
  FILE *fp = fopen(path, "rb");
  if (!fp) {
    ESP_LOGE("anim", "failed to open %s", path);
    return;
  }
  // uint8_t frame_bytes[1024];
  uint8_t *frame_bytes = malloc(1024);
  if (!frame_bytes) {
    ESP_LOGE("anim", "malloc failed");
    fclose(fp);
    return;
  }
  fread(frame_bytes, 1, 1024, fp);
  fclose(fp);
  draw_frame(frame_bytes);
  free(frame_bytes);
}
