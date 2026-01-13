#include "states_functions.h"

void Increment_Target_LGH(uint8_t* index){
    (*index)++;
    if ((*index) >= NUMBER_OF_LIGHTHOUSES) {
        (*index) = 0;
    }
}