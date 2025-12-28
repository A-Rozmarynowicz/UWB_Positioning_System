#include "Measure.h"

double time_response_offset = 0.0;
float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES] = {0};

double Get_Elapsed_Time_From_Measurements(uint32_t first_registered_time, uint32_t second_registered_time, double time_offset){
    uint32_t travel_cycle_counts = 0;
    if (first_registered_time > second_registered_time){
      travel_cycle_counts = (CYCLE_COUNT_MAX - first_registered_time) + second_registered_time;
    }
    else {
      travel_cycle_counts = second_registered_time - first_registered_time;
    }
    double period = 1.0 / (((double) ESP.getCpuFreqMHz() * 10e6));
    double elapsed_time = ((double) travel_cycle_counts * period) - time_offset;
    return elapsed_time;
}

void Calculate_Distance_To_Target(double measured_times_sum, uint16_t completed_measurements, double avg_response_time, uint8_t current_target){
  float distance = (C_SPEED/2.0) *
                  ( ((measured_times_sum)/((float) completed_measurements)) - avg_response_time);
  distances_to_lighthouses[current_target] = distance;
}
