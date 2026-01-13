#include "calculations.h"

float distances_to_lghs[NUMBER_OF_LIGHTHOUSES] = {0};
Position lghs_positions[NUMBER_OF_LIGHTHOUSES] = {0};
Position current_position = {0};

void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance){
    distances_to_lghs[lgh_index] = new_distance;
}

void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z){
    lghs_positions[lgh_index].x = x;
    lghs_positions[lgh_index].y = y;
    lghs_positions[lgh_index].z = z;
}

void Estimate_Position(){}