/**
 * @file lcd_handler.h
 * @brief LCD display handling and transmission queue utilities.
 *
 * @details
 * This header defines constants, types, and shared variables used to manage
 * an LCD display over I2C, including a software queue for asynchronous
 * transmission.
 *
 * It provides:
 * - LCD command and data queue management
 * - LCD initialization and cursor positioning
 * - String printing functions
 * - Callback functions for I2C transmission handling
 */

#ifndef INC_LCD_HANDLER_H_
#define INC_LCD_HANDLER_H_

#include <string.h>
#include <stdio.h>
#include "stm32l4xx_hal.h"

/** @brief I2C address of the LCD (7-bit address shifted left).*/
#define SLAVE_ADDRESS_LCD 0x4E

/** @brief Maximum number of bytes that can be queued for transmission. */
#define QUEUE_SIZE 512

/** @brief Size of a single LCD command in bytes. */
#define COMMAND_SIZE 4

/** @brief X coordinate positions on the LCD. */
extern const uint8_t X_LCD_COORDS[2];

/** @brief Y coordinate positions on the LCD. */
extern const uint8_t Y_LCD_COORDS[2];

/** @brief Z coordinate positions on the LCD. */
extern const uint8_t Z_LCD_COORDS[2];

/** @brief R coordinate positions on the LCD. */
extern const uint8_t R_LCD_COORDS[2];

/** @brief LCD message width in characters. */
extern const uint8_t LCD_MESSAGE_WIDTH;

/**
 * @brief LCD operation status codes.
 *
 * @details
 * Returned by public functions to indicate success or error conditions.
 */
typedef enum LCD_Status {
	LCD_OK = 0,
	LCD_QUEUE_FULL = 1,
	LCD_QUEUE_EMPTY = 2,
	LCD_INIT_FAIL = 3,
	LCD_HAL_ERROR = 4,
} LCD_Status;

/** @brief I2C handle used for communication with the LCD. */
extern I2C_HandleTypeDef* h_lcd_i2c;

/** @brief Queue buffer for outgoing LCD commands/data. */
extern uint8_t tx_queue[QUEUE_SIZE];

/** @brief Index where new data is appended in the queue. */
extern uint16_t head_pointer; // Where we append to

/** @brief Index from which data is transmitted from the queue. */
extern uint16_t tail_pointer; // Where we send from


/** @brief Flag indicating if an I2C transmission is currently in progress. */
extern uint8_t transmission_going;

// Public
LCD_Status Initialize_LCD_Handler(I2C_HandleTypeDef* i2c_handle);
LCD_Status Put_Cursor(uint8_t row, uint8_t column);
LCD_Status Print_String(char* txt, uint8_t size);
LCD_Status Print_String_At_Pos(char* txt, uint8_t size, uint8_t row, uint8_t column);

LCD_Status Print_Whole_Position(float x, float y, float z, float R);

// Private
LCD_Status _lcd_init(void);

LCD_Status _add_command_to_queue(char cmd);
LCD_Status _add_data_to_queue(char data);
LCD_Status _cd_send_cmd (char cmd);

HAL_StatusTypeDef _begin_transmission();
void _stop_transmission();
uint8_t _is_transmission_going();
void _increase_tail_pointer(uint16_t inc);

uint8_t _has_queue_space(uint16_t data_size);
LCD_Status _copy_buffer_to_queue(uint8_t* buffer);

HAL_StatusTypeDef _send_one_byte();

HAL_StatusTypeDef _lcd_i2c_transmit_it_callback(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef _lcd_i2c_receive_it_callback(I2C_HandleTypeDef *hi2c);

#endif /* INC_LCD_HANDLER_H_ */
