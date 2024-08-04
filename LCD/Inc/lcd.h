#ifndef __LCD_16x2_H__
#define __LCD_16x2_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#define I2C_ADDR 0x27 // I2C address of the PCF8574
#define RS_BIT 0 // Register select bit
#define EN_BIT 2 // Enable bit
#define BL_BIT 3 // Backlight bit
#define D4_BIT 4 // Data 4 bit
#define D5_BIT 5 // Data 5 bit
#define D6_BIT 6 // Data 6 bit
#define D7_BIT 7 // Data 7 bit

#define LCD_ROWS 2 // Number of rows on the LCD
#define LCD_COLS 16 // Number of columns on the LCD


void LCD_write_nibble(uint8_t nibble, uint8_t rs);
void LCD_send_cmd(uint8_t cmd);
void LCD_send_data(uint8_t data);
void LCD_init();
void LCD_write_string(char *str);
void LCD_set_cursor(uint8_t row, uint8_t column);
void LCD_clear(void);
void LCD_backlight(uint8_t state);

#ifdef __cplusplus
}
#endif

#endif


