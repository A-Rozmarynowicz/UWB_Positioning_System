/*
 * lcd_handler.h
 *
 *  Created on: Jan 7, 2026
 *      Author: arekr
 */

#ifndef INC_LCD_HANDLER_H_
#define INC_LCD_HANDLER_H_

#include <string.h>
#include <stdio.h>
#include "stm32l4xx_hal.h"

#define SLAVE_ADDRESS_LCD 0x4E
#define QUEUE_SIZE 512
#define COMMAND_SIZE 4

extern const uint8_t X_LCD_COORDS[2];
extern const uint8_t Y_LCD_COORDS[2];
extern const uint8_t Z_LCD_COORDS[2];


typedef enum LCD_Status {
	LCD_OK = 0,
	LCD_QUEUE_FULL = 1,
	LCD_QUEUE_EMPTY = 2,
	LCD_INIT_FAIL = 3,
	LCD_HAL_ERROR = 4,
} LCD_Status;

extern I2C_HandleTypeDef* h_lcd_i2c;
extern uint8_t tx_queue[QUEUE_SIZE];
extern uint16_t head_pointer; // Where we append to
extern uint16_t tail_pointer; // Where we send from

extern uint8_t transmission_going;

// Public
LCD_Status Initialize_LCD_Handler(I2C_HandleTypeDef* i2c_handle);
LCD_Status Put_Cursor(uint8_t row, uint8_t column);
LCD_Status Print_String(char* txt, uint8_t size);
LCD_Status Print_String_At_Pos(char* txt, uint8_t size, uint8_t row, uint8_t column);

LCD_Status Print_Whole_Position(float x, float y, float z);

// Private
LCD_Status lcd_init(void);

LCD_Status add_command_to_queue(char cmd);
LCD_Status add_data_to_queue(char data);
LCD_Status lcd_send_cmd (char cmd);

HAL_StatusTypeDef begin_transmission();
void stop_transmission();
uint8_t is_transmission_going();
void increase_tail_pointer(uint16_t inc);

uint8_t has_queue_space(uint16_t data_size);
LCD_Status copy_buffer_to_queue(uint8_t* buffer);

HAL_StatusTypeDef send_one_byte();

void lcd_i2c_transmit_callback(I2C_HandleTypeDef *hi2c);
void lcd_i2c_receive_callback(I2C_HandleTypeDef *hi2c);

#endif /* INC_LCD_HANDLER_H_ */
