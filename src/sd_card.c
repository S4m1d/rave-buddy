#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"

#define PIN_CS 5
#define PIN_MOSI 23
#define PIN_MISO 19
#define PIN_SCK 18

static const char *TAG = "sdcard";
static sdmmc_card_t *card = NULL;

esp_err_t sd_card_init() {
  vTaskDelay(pdMS_TO_TICKS(1000));

  spi_bus_config_t bus_cfg = {
      .mosi_io_num = PIN_MOSI,
      .miso_io_num = PIN_MISO,
      .sclk_io_num = PIN_SCK,
      .quadwp_io_num = -1,
      .quadhd_io_num = -1,
      .max_transfer_sz = 4096,
  };

  esp_err_t ret = spi_bus_initialize(SPI2_HOST, &bus_cfg, SPI_DMA_CH_AUTO);
  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "failed to initialize SPI bus: %s", esp_err_to_name(ret));
    return ret;
  }

  gpio_set_pull_mode(PIN_MISO, GPIO_PULLUP_ONLY);

  sdmmc_host_t host = SDSPI_HOST_DEFAULT();
  host.max_freq_khz = 400;
  host.slot = SPI2_HOST;

  sdspi_device_config_t slot_cfg = SDSPI_DEVICE_CONFIG_DEFAULT();
  slot_cfg.gpio_cs = PIN_CS;
  slot_cfg.host_id = SPI2_HOST;

  esp_vfs_fat_sdmmc_mount_config_t mount_cfg = {
      .format_if_mount_failed = false,
      .max_files = 5,
      .allocation_unit_size = 16 * 1024,
  };

  ret = esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_cfg, &mount_cfg, &card);
  if (ret != ESP_OK) {
    ESP_LOGE(TAG, "failed to mount: %s", esp_err_to_name(ret));
    return ret;
  }

  ESP_LOGI(TAG, "SD card mounted");
  sdmmc_card_print_info(stdout, card);
  return ESP_OK;
}
