#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "observer_config.h"

typedef struct Position {
    float x;
    float y;
    float z;
} Position;

extern float distances_to_lghs[NUMBER_OF_LIGHTHOUSES];

extern Position current_position;

void Estimate_Position();

#endif