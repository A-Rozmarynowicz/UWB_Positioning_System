/*
 * lcd_handler.h
 *
 *  Created on: Jan 7, 2026
 *      Author: arekr
 */

#ifndef INC_LCD_HANDLER_H_
#define INC_LCD_HANDLER_H_

#include "stm32l4xx_hal.h"

#define SLAVE_ADDRESS_LCD 0x4E

extern I2C_HandleTypeDef* h_lcd_i2c;

void initialize_handler(I2C_HandleTypeDef* i2c_handle);
void lcd_init (void);
void lcd_send_data (char data);
void lcd_send_string (char *str);
void lcd_put_cur(int row, int col);
void lcd_send_cmd (char cmd);

#endif /* INC_LCD_HANDLER_H_ */
