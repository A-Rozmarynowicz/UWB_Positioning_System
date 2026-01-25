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
struct Position initial_position = {0};

// Public
HAL_StatusTypeDef Initialize_Observer_Comm(TIM_HandleTypeDef* refresh_tim_handle, UART_HandleTypeDef* obs_uart_handle){
	refresh_info_timer_h = refresh_tim_handle;
	obs_uart_h = obs_uart_handle;
	HAL_TIM_Base_Start_IT(refresh_info_timer_h);
	return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, OBSERVER_MESSAGE_SIZE);
}

float Get_Position_Vector_Length(struct Position* pos){
	return (pos->x)*(pos->x) + (pos->y)*(pos->y) + (pos->z)*(pos->z);
}

// Private
void _read_position(){
	if ((Get_Position_Vector_Length(&initial_position) == 0.0f) && (Get_Position_Vector_Length(&current_position) != 0.0f)){
		memcpy(&initial_position, &current_position, sizeof(struct Position));
	}
	memcpy(&current_position, &(obs_uart_receive_buffer[OBS_POSITION_STRUCT]), sizeof(float)*3);
	current_position.x -= initial_position.x;
	current_position.y -= initial_position.y;
	current_position.z -= initial_position.z;
}

LCD_Status _print_position_to_lcd(){
	return Print_Whole_Position(current_position.x, current_position.y, current_position.z, Get_Position_Vector_Length(&current_position));
};

HAL_StatusTypeDef _obs_timer_period_elapsed_it_callback(TIM_HandleTypeDef *htim){
	if (htim == refresh_info_timer_h){
		 if ( _print_position_to_lcd() != LCD_OK){
			 return HAL_ERROR;
		 }
	}
	return HAL_OK;
};

HAL_StatusTypeDef _obs_uart_receive_it_callback(UART_HandleTypeDef *huart){
	if (huart == obs_uart_h){
		_read_position();
		return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, OBSERVER_MESSAGE_SIZE);
	}
	return HAL_OK;
};

HAL_StatusTypeDef _obs_uart_transmit_it_callback(UART_HandleTypeDef *huart){
	return HAL_OK;
};

