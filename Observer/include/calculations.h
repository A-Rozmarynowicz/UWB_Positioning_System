#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "observer_config.h"

typedef struct Position {
    float x;
    float y;
    float z;
} Position;

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

void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance);
void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z);
void Estimate_Position();

void Build_A_Matrix();
void Build_AT_Matrix();
void Build_ATA_Matrix();
uint8_t Build_ATA_Inv_Matrix();
void Build_B_Vector_Constants();
void Build_B_Vector();
void Calculate_ATB_Matrix();
void Calculate_Solution();

#endif