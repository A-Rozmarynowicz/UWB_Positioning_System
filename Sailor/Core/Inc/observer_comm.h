/**
 * @file observer_comm.h
 * @brief Observer communication module header.
 *
 * This file defines the interface for communicating with the observer module
 * via UART. It contains configuration constants, data structures, global variables,
 * public API functions, and private helper functions and callbacks.
 *
 */

#ifndef INC_OBSERVER_COMM_H_
#define INC_OBSERVER_COMM_H_

#include "lcd_handler.h"
#include "stm32l4xx_hal.h"
#include "string.h"

#define OBSERVER_MESSAGE_SIZE 16


/**
 * @enum Observer_Info_Setup
 * @brief Defines byte offsets in the observer message payload.
 */
typedef enum Observer_Info_Setup {
	OBS_ERROR_CODE = 0,
	OBS_POSITION_STRUCT = 4,
} Observer_Info_Setup;


/**
 * @struct Position
 * @brief Represents a 3D position vector.
 */
struct Position {
	float x;
	float y;
	float z;
};

/**
 * @brief Handle to the refresh timer used for periodic LCD updates.
 */
extern TIM_HandleTypeDef* refresh_info_timer_h;

/**
 * @brief UART handle used for communication with the observer device.
 */
extern UART_HandleTypeDef* obs_uart_h;

/**
 * @brief Current calculated position of the device.
 */
extern struct Position current_position;

/**
 * @brief Initial position stored at 1st measurement.
 */
extern struct Position initial_position;

/**
 * @brief UART receive buffer for incoming observer messages.
 */
extern uint8_t obs_uart_receive_buffer[OBSERVER_MESSAGE_SIZE];

// Public
HAL_StatusTypeDef Initialize_Observer_Comm(TIM_HandleTypeDef* refresh_tim_handle, UART_HandleTypeDef* obs_uart_handle);
float Get_Position_Vector_Length(struct Position* pos);

// Private
void _read_position();
LCD_Status _print_position_to_lcd();

HAL_StatusTypeDef _obs_timer_period_elapsed_it_callback(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef _obs_uart_receive_it_callback(UART_HandleTypeDef *huart);
HAL_StatusTypeDef _obs_uart_transmit_it_callback(UART_HandleTypeDef *huart);

#endif /* INC_OBSERVER_COMM_H_ */
