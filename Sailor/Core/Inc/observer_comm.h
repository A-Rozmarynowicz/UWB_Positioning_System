/*
 * observer_comm.h
 *
 *  Created on: Jan 7, 2026
 *      Author: arekr
 */

#ifndef INC_OBSERVER_COMM_H_
#define INC_OBSERVER_COMM_H_

#include "lcd_handler.h"
#include "stm32l4xx_hal.h"
#include "string.h"

#define OBSERVER_MESSAGE_SIZE 16

typedef enum Observer_Info_Setup {
	OBS_ERROR_CODE = 0,
	OBS_POSITION_STRUCT = 4,
} Observer_Info_Setup;

struct Position {
	float x;
	float y;
	float z;
};

extern TIM_HandleTypeDef* refresh_info_timer_h;
extern UART_HandleTypeDef* obs_uart_h;

extern struct Position current_position;
extern uint8_t obs_uart_receive_buffer[OBSERVER_MESSAGE_SIZE];

// Public
HAL_StatusTypeDef Initialize_Observer_Comm(TIM_HandleTypeDef* refresh_tim_handle, UART_HandleTypeDef* obs_uart_handle);

// Private
LCD_Status _print_position_to_lcd();

HAL_StatusTypeDef _obs_timer_period_elapsed_it_callback(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef _obs_uart_receive_it_callback(UART_HandleTypeDef *huart);
HAL_StatusTypeDef _obs_uart_transmit_it_callback(UART_HandleTypeDef *huart);

#endif /* INC_OBSERVER_COMM_H_ */
