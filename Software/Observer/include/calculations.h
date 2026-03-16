/**
 * @file calculations.h
 * @brief Position estimation and matrix calculations for the observer.
 *
 * @details
 * This header defines constants, global variables, and function declarations
 * used to estimate the position of the observer device based on UWB distance
 * measurements to multiple lighthouses.
 *
 * It provides:
 * - Measurement limits and constants
 * - Storage for distance measurements and lighthouse positions
 * - Matrices and vectors for least-squares position estimation
 * - Public API for updating distances and calculating position
 */

#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "observer_config.h"

/**
 * @brief Maximum expected distance between a tag and any lighthouse.
 *
 * Used to filter out unrealistic measurements.
 */
const float THEORETICAL_MAX_DISTANCE = 10.0f;

/**
 * @brief Compensation for antena delay [meters].
 */
const float ANTENNA_DELAY_OFFSET = 0.1f;

/**
 * @brief Minimum number of distance measurements required per lighthouse.
 */
const uint8_t MINIMUM_MEASUREMENTS_PER_LGH = 25;

/**
 * @brief Maximum number of distance measurements stored per lighthouse.
 */
const uint8_t MAXIMUM_MEASUREMENT_PER_LGH = 250;

/**
 * @brief Number of completed measurements for each lighthouse.
 */
extern uint16_t distances_measurements_completed[NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Current averaged distance to each lighthouse.
 */
extern float distances_to_lghs[NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Known positions of all lighthouses.
 */
extern Position lghs_positions[NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Vector containing constants used in B vector calculation.
 */
extern float B_vector_constants[NUMBER_OF_LIGHTHOUSES];

/** @defgroup Matrices Matrices
 *  @brief All the neccessary matrices and vectors.
 *  @{
 */
extern float A_matrix[NUMBER_OF_LIGHTHOUSES-1][3];
extern float AT_matrix[3][NUMBER_OF_LIGHTHOUSES-1];
extern float ATA_matrix[3][3];
extern float ATA_inv_matrix[3][3];
extern float B_vector[NUMBER_OF_LIGHTHOUSES-1];
extern float solution_vector[3];
extern float ATB_vector[3];
/** @} */

/**
 * @brief Estimated current position of the device.
 */
extern Position current_position;

// Public
void Estimate_Position();
void Build_Constant_Matrices();
void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance);
int8_t Get_LGH_From_Short_Address(const uint16_t short_address);
uint16_t Get_Short_Address_From_Long(const uint8_t* address);
void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z);
bool Are_Enough_Measurements_Complete();
void Calculations_Error();

// Private
void _build_a_matrix();
void _build_at_matrix();
void _build_ata_matrix();
uint8_t _build_ata_inv_matrix();
void _build_b_vector_constants();
void _build_b_vector();
void _calculate_atb_vector();
void _calculate_solution();
void _average_results();

void _flush_distance_measurements();

#endif