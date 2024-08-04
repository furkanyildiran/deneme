#include "lcd.h"
uint8_t backlight_state = 1;

/* Private variables */
extern I2C_HandleTypeDef hi2c1;

void LCD_write_nibble(uint8_t nibble, uint8_t rs) {
  uint8_t data = nibble << D4_BIT;
  data |= rs << RS_BIT;
  data |= backlight_state << BL_BIT; // Include backlight state in data
  data |= 1 << EN_BIT;
  HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR << 1, &data, 1, 100);
  HAL_Delay(1);
  data &= ~(1 << EN_BIT);
  HAL_I2C_Master_Transmit(&hi2c1, I2C_ADDR << 1, &data, 1, 100);
}

void LCD_send_cmd(uint8_t cmd) {
  uint8_t upper_nibble = cmd >> 4;
  uint8_t lower_nibble = cmd & 0x0F;
  LCD_write_nibble(upper_nibble, 0);
  LCD_write_nibble(lower_nibble, 0);
  if (cmd == 0x01 || cmd == 0x02) {
    HAL_Delay(2);
  }
}

void LCD_send_data(uint8_t data) {
  uint8_t upper_nibble = data >> 4;
  uint8_t lower_nibble = data & 0x0F;
  LCD_write_nibble(upper_nibble, 1);
  LCD_write_nibble(lower_nibble, 1);
}

void LCD_init() {
  HAL_Delay(50);
  LCD_write_nibble(0x03, 0);
  HAL_Delay(5);
  LCD_write_nibble(0x03, 0);
  HAL_Delay(1);
  LCD_write_nibble(0x03, 0);
  HAL_Delay(1);
  LCD_write_nibble(0x02, 0);
  LCD_send_cmd(0x28);
  LCD_send_cmd(0x0C);
  LCD_send_cmd(0x06);
  LCD_send_cmd(0x01);
  HAL_Delay(2);
}

void LCD_write_string(char *str) {
  while (*str) {
	  LCD_send_data(*str++);
  }
}

void LCD_set_cursor(uint8_t row, uint8_t column) {
    uint8_t address;
    switch (row) {
        case 0:
            address = 0x00;
            break;
        case 1:
            address = 0x40;
            break;
        default:
            address = 0x00;
    }
    address += column;
    LCD_send_cmd(0x80 | address);
}

void LCD_clear(void) {
	LCD_send_cmd(0x01);
    HAL_Delay(2);
}

void LCD_backlight(uint8_t state) {
  if (state) {
    backlight_state = 1;
  } else {
    backlight_state = 0;
  }
}
