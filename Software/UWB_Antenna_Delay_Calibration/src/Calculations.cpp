#include "Calculations.h"

float distance_sum;
float distance_estimation;
uint32_t current_number_of_measurements = 0;

void New_Measurement(float distance)
{
    if (Is_Enough_Measurements()) {
        return;
    }
    distance_sum += distance;
    current_number_of_measurements += 1;
}

bool Is_Enough_Measurements()
{
    return current_number_of_measurements >= TARGET_NUMBER_OF_MEASUREMENTS;
}

void Estimate_Distance()
{
    if (current_number_of_measurements == 0) {
        return;
    }
    distance_estimation = distance_sum / current_number_of_measurements;
}


float Get_Estimated_Distance()
{
    return distance_estimation;
}

float Get_Biased_Range_Value(float range)
{
    return range + range*A_poly_param + B_poly_param;
}
