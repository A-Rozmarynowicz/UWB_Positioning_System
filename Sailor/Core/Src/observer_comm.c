/*
 * observer_comm.c
 *
 *  Created on: Jan 7, 2026
 *      Author: arekr
 */

#include "observer_comm.h"

TIM_HandleTypeDef* refresh_info_timer_h = 0;
UART_HandleTypeDef* obs_uart_h = 0;
uint8_t obs_uart_receive_buffer[OBSERVER_MESSAGE_SIZE] = {0};

struct Position current_position = {0};

HAL_StatusTypeDef Initialize_Observer_Comm(TIM_HandleTypeDef* refresh_tim_handle, UART_HandleTypeDef* obs_uart_handle){
	refresh_info_timer_h = refresh_tim_handle;
	obs_uart_h = obs_uart_handle;

	return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, 12);
}

void print_position_to_lcd(){
	memcpy(&current_position, &(obs_uart_receive_buffer[OBS_POSITION_STRUCT]), sizeof(float)*3);
	Print_Whole_Position(current_position.x, current_position.y, current_position.z);
};

void obs_timer_period_elapsed_it_callback(TIM_HandleTypeDef *htim){
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	print_position_to_lcd();
};

HAL_StatusTypeDef obs_uart_receive_it_callback(UART_HandleTypeDef *huart){
	if (huart == obs_uart_h){
		return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, 12);
	}
	return HAL_OK;
};

HAL_StatusTypeDef obs_uart_transmit_it_callback(UART_HandleTypeDef *huart){
	return HAL_OK;
};

