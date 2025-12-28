#ifndef MEASURE_H
#define MEASURE_H
#include "LighthouseConfig.h"

#define NUMBER_OF_LIGHTHOUSES (uint8_t) 2

const float C_SPEED = 299792458.0; // m/s
extern double time_response_offset;
extern float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES];

double Get_Elapsed_Time_From_Measurements(uint32_t receive_time, uint32_t send_time, double time_offset=0.0);
void Calculate_Distance_To_Target(double measured_times_sum, uint16_t completed_measurements, double avg_response_time, uint8_t current_target);

#endif