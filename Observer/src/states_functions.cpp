#include "states_functions.h"

/**
 * @brief Increments current target lighthouse index.
 *
 * @param index Pointer to current target index
 *
 * @return void
 */
void Increment_Target_LGH(uint8_t* index){
    (*index)++;
    if ((*index) >= NUMBER_OF_LIGHTHOUSES) {
        (*index) = 0;
    }
}