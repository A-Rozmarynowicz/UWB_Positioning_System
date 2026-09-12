#ifndef MEASURE_H
#define MEASURE_H
#include <Arduino.h>


const uint32_t TARGET_NUMBER_OF_MEASUREMENTS = 1000;

extern float distance_sum;
extern float distance_estimation;
extern uint32_t current_number_of_measurements;

void New_Measurement(float distance);
bool Is_Enough_Measurements();
void Estimate_Distance();
float Get_Estimated_Distance();

#endif