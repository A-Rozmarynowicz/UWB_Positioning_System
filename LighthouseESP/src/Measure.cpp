#include "Measure.h"
#include <math.h>

double time_response_offset = 0.0;
float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES] = {0};
float master_all_distances_matrix[NUMBER_OF_LIGHTHOUSES][NUMBER_OF_LIGHTHOUSES] = {0};
Position master_all_positions[NUMBER_OF_LIGHTHOUSES] = {0};
Position position = {0};

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

void Print_Master_All_Distances_Matrix(){
  for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        for (uint8_t j=0;j<NUMBER_OF_LIGHTHOUSES;j++){
            printf("%4f ", master_all_distances_matrix[i][j]);
        }
        printf("\n");
    }
}

void Calculate_Position_Of_Lighthouse(uint8_t lighthouse){
  if (lighthouse == 0) {
  }
  else if (lighthouse == 1){
    Set_LGH_1_Position();
  }
  else if (lighthouse == 2){
    Set_LGH_2_Position();
  }
  else if (lighthouse == 3){
    Set_LGH_3_Position();
  }
  else {
    Set_LGH_4Plus_Position(lighthouse);
  }
}

void Set_LGH_1_Position(){
  float distance = (master_all_distances_matrix[0][1] + master_all_distances_matrix[1][0])/2.0;
  master_all_positions[1].x = distance;
}

void Set_LGH_2_Position(){
  float R0 = (master_all_distances_matrix[0][2] + master_all_distances_matrix[2][0])/2.0;
  float R1 = (master_all_distances_matrix[1][2] + master_all_distances_matrix[2][1])/2.0;
  float x1 = master_all_positions[1].x;
  float x = ((R1*R1 - R0*R0)/(-2*x1)) + (x1)/2.0;
  float y_sugg = R0*R0 + R1*R1 - 2*x*x + 2*x*x1 - x1*x1;
  float y = 0.0;
  if (y_sugg <= 0.0){
    y = 0.1;
  }
  else {
    y = sqrtf(y_sugg/2);
  }
  master_all_positions[2].x = x;
  master_all_positions[2].y = y;
}

void Set_LGH_3_Position(){
  float R0 = (master_all_distances_matrix[0][3] + master_all_distances_matrix[3][0])/2.0;
  float R1 = (master_all_distances_matrix[1][3] + master_all_distances_matrix[3][1])/2.0;
  float R2 = (master_all_distances_matrix[2][3] + master_all_distances_matrix[3][2])/2.0;

  float x1 = master_all_positions[1].x;
  float x2 = master_all_positions[2].x;
  float y2 = master_all_positions[2].y;

  float x = (R1*R1 - R0*R0 - x1*x1)/(-2*x1);
  float y = (R2*R2 - R0*R0 - y2*y2 - x2*x2 + 2*x2*x)/(-2*y2);
  float z_sugg = R0*R0 + R1*R1 + R2*R2 + 2*x1*x - x1*x1 + 2*x2*x - x2*x2 + 2*y2*y - y2*y2 - 3*x*x - 3*y*y;
  float z = 0.0;
  if (z_sugg > 0.0) {
    z = sqrtf(z_sugg/3.0);
  }
  else {
    z = 0.1;
  }

  master_all_positions[3].x = x;
  master_all_positions[3].y = y;
  master_all_positions[3].z = z;
}

void Set_LGH_4Plus_Position(uint8_t lighthouse){

}

void Print_Position(uint8_t lighthouse){
  Serial.printf("Position of LGH number: %d: ", lighthouse);
  Serial.printf("x=%0.2f || y=%0.2f || z=%0.2f \n", master_all_positions[lighthouse].x, master_all_positions[lighthouse].y, master_all_positions[lighthouse].z);
}