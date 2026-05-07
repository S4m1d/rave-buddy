#include "ssd1306.h"
#include "driver/i2c.h"
#include <stdint.h>

void i2c_init(void) {
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

// I2C protocol with SSD1306 specifics sequence: START -> Device Address -> mode
// bytes (0x00 for cmd or 0x40 for pixels data) -> data or command bytes -> STOP
void ssd1306_cmd(uint8_t cmd) {
  i2c_cmd_handle_t handle = i2c_cmd_link_create();
  i2c_master_start(handle);
  i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(handle, 0x00, true); // Co=0, D/C=0 (command)
  i2c_master_write_byte(handle, cmd, true);
  i2c_master_stop(handle);
  i2c_master_cmd_begin(I2C_MASTER_NUM, handle, pdMS_TO_TICKS(100));
  i2c_cmd_link_delete(handle);
}

void ssd1306_init(void) {
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

void ssd1306_cmd_set_page(uint8_t page) { ssd1306_cmd(0xB0 + page); }

void ssd1306_cmd_set_col(uint8_t col) {
  ssd1306_cmd(0x0F & col);      // low nibble
  ssd1306_cmd(0x10 | col >> 4); // high nibble
}

void ssd1306_set_mode(i2c_cmd_handle_t handle, enum Ssd1306Mode m) {
  switch (m) {
  case Data:
    i2c_master_write_byte(handle, 0x40, true);
    break;
  case Cmd:
    i2c_master_write_byte(handle, 0x00, true);
    break;
  }
}

void ssd1306_set_as_i2c_device(i2c_cmd_handle_t handle, int mode) {
  i2c_master_write_byte(handle, (SSD1306_ADDR << 1) | mode, true);
}

void ssd1306_write_page(i2c_cmd_handle_t handle, uint8_t data) {
  i2c_master_write_byte(handle, data, true);
}
