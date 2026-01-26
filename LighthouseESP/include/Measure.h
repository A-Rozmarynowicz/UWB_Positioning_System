/**
 * @file Measure.h
 * @brief Distance measurement and position calculation utilities.
 *
 * @details
 * This header defines data structures, constants, and shared variables used
 * for distance measurement processing and position estimation of Lighthouse
 * devices within the system.
 *
 * It provides:
 * - Limits and parameters related to distance measurements
 * - A 3D position structure
 * - Global buffers storing distances and calculated positions
 */

#ifndef MEASURE_H
#define MEASURE_H
#include "LighthouseConfig.h"

/**
 * @brief Theoretical maximum valid distance between devices [meters].
 */
const float THEORETICAL_MAX_DISTANCE = 12.0f;

/**
 * @brief Minimum number of distance measurements required for processing.
 */
const uint8_t MIN_DISTANCE_MEASUREMENTS = 50;

/**
 * @brief Maximum number of distance measurements required for processing.
 */
const uint8_t MAX_DISTANCE_MEASUREMENTS = 250;

/**
 * @brief Antenna delay compensation offset applied to distance measurements [meters].
 */
const float DISTANCE_ANTENA_DELAY_OFFSET = 0.0;

/**
 * @struct Position
 * @brief 3D Cartesian position representation.
 */
struct Position {
    float x;
    float y;
    float z;
};

/**
 * @brief Distances measured to all lighthouses.
 */
extern float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Matrix containing distances between all lighthouse pairs.
 */
extern float master_all_distances_matrix[NUMBER_OF_LIGHTHOUSES][NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Calculated positions of all lighthouses.
 */
extern Position master_all_positions[NUMBER_OF_LIGHTHOUSES];

/**
 * @brief Current device position.
 */
extern Position position;

// Public
void New_Measurement(uint8_t lighthouse, float distance);
void Calculate_Distance_To_Targets(uint8_t distance_measurements[NUMBER_OF_LIGHTHOUSES]);
void Print_Master_All_Distances_Matrix();
void Print_Position(uint8_t lighthouse);
void Calculate_Position_Of_Lighthouse(uint8_t lighthouse);

// Private
void _set_LGH_1_position();
void _set_LGH_2_position();
void _set_LGH_3_position();
void _set_LGH_4plus_position(uint8_t lighthouse);

#endif