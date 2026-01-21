#ifndef MEASURE_H
#define MEASURE_H
#include "LighthouseConfig.h"

const uint8_t MIN_DISTANCE_MEASUREMENTS = 5;
const float DISTANCE_ANTENA_DELAY_OFFSET = 0.6;
// const float /DISTANCE_ANTENA_DELAY_OFFSET = 0.0;

struct Position {
    float x;
    float y;
    float z;
};

extern float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES];
extern float master_all_distances_matrix[NUMBER_OF_LIGHTHOUSES][NUMBER_OF_LIGHTHOUSES];
extern Position master_all_positions[NUMBER_OF_LIGHTHOUSES];
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