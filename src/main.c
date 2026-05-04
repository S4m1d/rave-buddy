#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_FREQ_HZ 400000
#define I2C_MASTER_NUM I2C_NUM_0
#define SSD1306_ADDR 0x3C

static void i2c_init(void) {
  i2c_config_t conf = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = I2C_MASTER_SDA_IO,
      .scl_io_num = I2C_MASTER_SCL_IO,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = I2C_MASTER_FREQ_HZ,
  };
  i2c_param_config(I2C_MASTER_NUM, &conf);
  i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

static void ssd1306_cmd(uint8_t cmd) {
  i2c_cmd_handle_t handle = i2c_cmd_link_create();
  i2c_master_start(handle);
  i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(handle, 0x00, true); // Co=0, D/C=0 (command)
  i2c_master_write_byte(handle, cmd, true);
  i2c_master_stop(handle);
  i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
  i2c_cmd_link_delete(handle);
}

static void ssd1306_init(void) {
  vTaskDelay(pdMS_TO_TICKS(100));
  ssd1306_cmd(0xAE); // display off
  ssd1306_cmd(0x20); // memory addressing mode
  ssd1306_cmd(0x00); // horizontal
  ssd1306_cmd(0xB0); // page start
  ssd1306_cmd(0xC8); // COM scan direction
  ssd1306_cmd(0x00); // low column
  ssd1306_cmd(0x10); // high column
  ssd1306_cmd(0x40); // start line
  ssd1306_cmd(0x81); // contrast
  ssd1306_cmd(0xFF); // max contrast
  ssd1306_cmd(0xA1); // segment remap
  ssd1306_cmd(0xA6); // normal display
  ssd1306_cmd(0xA8); // multiplex ratio
  ssd1306_cmd(0x3F); // 64 rows (use 0x1F for 32 rows)
  ssd1306_cmd(0xA4); // output follows RAM
  ssd1306_cmd(0xD3); // display offset
  ssd1306_cmd(0x00);
  ssd1306_cmd(0xD5); // clock divide
  ssd1306_cmd(0xF0);
  ssd1306_cmd(0xD9); // pre-charge
  ssd1306_cmd(0x22);
  ssd1306_cmd(0xDA); // COM pins
  ssd1306_cmd(0x12);
  ssd1306_cmd(0xDB); // VCOMH deselect
  ssd1306_cmd(0x20);
  ssd1306_cmd(0x8D); // charge pump
  ssd1306_cmd(0x14); // enable
  ssd1306_cmd(0xAF); // display on
}

static void ssd1306_fill(uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

static void ssd1306_fill_half_upper(uint8_t pattern) {
  for (uint8_t page = 0; page <= 3; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

static void ssd1306_fill_half_lower(uint8_t pattern) {
  for (uint8_t page = 4; page < 8; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 128; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

static void ssd1306_fill_half_left(uint8_t pattern) {
  for (uint8_t page = 0; page < 8; page++) {
    ssd1306_cmd(0xB0 + page);
    ssd1306_cmd(0x00);
    ssd1306_cmd(0x10);
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_start(handle);
    i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(handle, 0x40, true); // data mode
    for (uint8_t i = 0; i < 64; i++) {
      i2c_master_write_byte(handle, pattern, true);
    }
    i2c_master_stop(handle);
    i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(handle);
  }
}

static void ssd1306_fill_half_right(uint8_t pattern) {
    for (uint8_t page = 0; page < 8; page++) {
        ssd1306_cmd(0xB0 + page);
        ssd1306_cmd(0x40 & 0x0F);  // low nibble of start column (64 = 0x40)
        ssd1306_cmd(0x10 | (0x40 >> 4)); // high nibble of start column
        i2c_cmd_handle_t handle = i2c_cmd_link_create();
        i2c_master_start(handle);
        i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(handle, 0x40, true);
        for (uint8_t i = 64; i < 128; i++) {  // only right 64 columns
            i2c_master_write_byte(handle, pattern, true);
        }
        i2c_master_stop(handle);
        i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
        i2c_cmd_link_delete(handle);
    }
}

void app_main(void) {
  i2c_init();
  ssd1306_init();
  ssd1306_fill(0x00); // all pixels off

  while (1) {
    ssd1306_fill_half_left(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_fill_half_left(0x00); // all pixels off

    ssd1306_fill_half_upper(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_fill_half_upper(0x00); // all pixels off

    ssd1306_fill_half_right(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_fill_half_right(0x00); // all pixels off

    ssd1306_fill_half_lower(0xFF); // all pixels on
    vTaskDelay(pdMS_TO_TICKS(1000));
    ssd1306_fill_half_lower(0x00); // all pixels off
  }
}
