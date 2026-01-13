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

extern Position current_position;

void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance);
void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z);
void Estimate_Position();

#endif