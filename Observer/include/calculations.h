#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "observer_config.h"


const uint8_t MINIMUM_MEASUREMENTS_PER_LGH = 10;
const uint8_t MAXIMUM_MEASUREMENT_PER_LGH = 50;

extern uint16_t distances_measurements_completed[NUMBER_OF_LIGHTHOUSES];
extern float distances_to_lghs[NUMBER_OF_LIGHTHOUSES];
extern Position lghs_positions[NUMBER_OF_LIGHTHOUSES];

extern float B_vector_constants[NUMBER_OF_LIGHTHOUSES];

extern float A_matrix[NUMBER_OF_LIGHTHOUSES-1][3];
extern float AT_matrix[3][NUMBER_OF_LIGHTHOUSES-1];
extern float ATA_matrix[3][3];
extern float ATA_inv_matrix[3][3];
extern float B_vector[NUMBER_OF_LIGHTHOUSES-1];
extern float solution_vector[3];
extern float ATB_vector[3];

extern Position current_position;

// Public
void Estimate_Position();
void Build_Constant_Matrices();
void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance);
int8_t Get_LGH_From_Short_Address(const uint16_t short_address);
uint16_t Get_Short_Address_From_Long(const uint8_t* address);
void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z);
bool Are_Enough_Measurements_Complete();
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