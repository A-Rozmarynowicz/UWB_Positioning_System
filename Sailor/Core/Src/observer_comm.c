#include <math.h>
#include "observer_comm.h"

TIM_HandleTypeDef* refresh_info_timer_h = 0;
UART_HandleTypeDef* obs_uart_h = 0;
uint8_t obs_uart_receive_buffer[OBSERVER_MESSAGE_SIZE] = {0};

struct Position current_position = {0};
struct Position initial_position = {0};

// Public

/**
 * @brief Initializes observer communication module.
 *
 * This function stores the provided timer and UART handles,
 * starts the timer interrupt, and begins UART DMA reception.
 *
 * @param refresh_tim_handle Pointer to the timer used for periodic LCD refresh.
 * @param obs_uart_handle Pointer to the UART interface used for communication.
 * @return HAL_OK if initialization succeeds, HAL error otherwise.
 */
HAL_StatusTypeDef Initialize_Observer_Comm(TIM_HandleTypeDef* refresh_tim_handle, UART_HandleTypeDef* obs_uart_handle){
	refresh_info_timer_h = refresh_tim_handle;
	obs_uart_h = obs_uart_handle;
	HAL_TIM_Base_Start_IT(refresh_info_timer_h);
	return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, OBSERVER_MESSAGE_SIZE);
}

/**
 * @brief Calculates squared length of a position vector.
 *
 * This function returns the squared Euclidean length of the position
 * vector. Squared length is used to avoid costly sqrt operations.
 *
 * @param pos Pointer to the Position structure.
 * @return Squared vector length.
 */
float Get_Position_Vector_Length(struct Position* pos){
	return sqrt((pos->x)*(pos->x) + (pos->y)*(pos->y) + (pos->z)*(pos->z));
}

// Private

/**
 * @brief Reads and updates current position from UART buffer.
 *
 * This function copies received position data from the UART buffer
 * and adjusts it relative to the initial position. The first received
 * non-zero position is stored as the initial reference.
 */
void _read_position(){
	if ((Get_Position_Vector_Length(&initial_position) == 0.0f) && (Get_Position_Vector_Length(&current_position) != 0.0f)){
		memcpy(&initial_position, &current_position, sizeof(struct Position));
	}
	memcpy(&current_position, &(obs_uart_receive_buffer[OBS_POSITION_STRUCT]), sizeof(float)*3);
	current_position.x -= initial_position.x;
	current_position.y -= initial_position.y;
	current_position.z -= initial_position.z;
}

/**
 * @brief Prints current position to the LCD display.
 *
 * This function prints the X, Y, Z coordinates and the total distance
 * from the initial position on the LCD using the LCD handler.
 *
 * @return LCD_OK if display is successful, LCD_HAL_ERROR otherwise.
 */
LCD_Status _print_position_to_lcd(){
	return Print_Whole_Position(current_position.x, current_position.y, current_position.z, Get_Position_Vector_Length(&current_position));
};

/**
 * @brief Timer interrupt callback handler.
 *
 * This function is called periodically by the timer interrupt.
 * If the interrupt source matches the refresh timer, the current
 * position is printed to the LCD.
 *
 * @param htim Pointer to the timer handle.
 * @return HAL_OK if handled correctly, HAL_ERROR otherwise.
 */
HAL_StatusTypeDef _obs_timer_period_elapsed_it_callback(TIM_HandleTypeDef *htim){
	if (htim == refresh_info_timer_h){
		 if ( _print_position_to_lcd() != LCD_OK){
			 return HAL_ERROR;
		 }
	}
	return HAL_OK;
};

/**
 * @brief UART receive complete interrupt handler.
 *
 * This function is called when UART DMA reception completes.
 * It updates the current position and restarts DMA reception.
 *
 * @param huart Pointer to the UART handle.
 * @return HAL_OK if handled correctly, HAL error otherwise.
 */
HAL_StatusTypeDef _obs_uart_receive_it_callback(UART_HandleTypeDef *huart){
	if (huart == obs_uart_h){
		_read_position();
		return HAL_UART_Receive_DMA(obs_uart_h, obs_uart_receive_buffer, OBSERVER_MESSAGE_SIZE);
	}
	return HAL_OK;
};

/**
 * @brief UART transmit complete interrupt handler.
 *
 * This function is currently unused but provided for completeness.
 *
 * @param huart Pointer to the UART handle.
 * @return HAL_OK always.
 */
HAL_StatusTypeDef _obs_uart_transmit_it_callback(UART_HandleTypeDef *huart){
	return HAL_OK;
};

