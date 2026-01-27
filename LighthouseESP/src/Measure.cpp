#include "Measure.h"
#include <math.h>

float distances_to_lighthouses[NUMBER_OF_LIGHTHOUSES] = {0};
float master_all_distances_matrix[NUMBER_OF_LIGHTHOUSES][NUMBER_OF_LIGHTHOUSES] = {0};
Position master_all_positions[NUMBER_OF_LIGHTHOUSES] = {0};
Position position = {0};

/**
 * @brief Add a new distance measurement from a lighthouse.
 *
 * The measurement is accumulated and later averaged. Values exceeding the
 * theoretical range are ignored.
 *
 * @param lighthouse ID of the lighthouse providing the measurement.
 * @param distance Measured distance value.
 * @return void
 */
void New_Measurement(uint8_t lighthouse, float distance){
  if (distance > THEORETICAL_MAX_DISTANCE || distance < -THEORETICAL_MAX_DISTANCE){
    return;
  }
  if (distance < DISTANCE_ANTENA_DELAY_OFFSET){
    distance = DISTANCE_ANTENA_DELAY_OFFSET;
  }
  completed_distance_measurements[lighthouse] += 1;
  distances_to_lighthouses[lighthouse] += distance;
}

/**
 * @brief Calculate averaged distances to all target lighthouses.
 *
 * Applies averaging based on the number of measurements and compensates
 * for antenna delay offset.
 *
 * @param distance_measurements Array containing number of measurements per lighthouse.
 * @return void
 */
void Calculate_Distance_To_Targets(uint8_t distance_measurements[NUMBER_OF_LIGHTHOUSES]){
  for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
    if (i == LIGHTHOUSE_ID){
      continue;
    }
    if (distance_measurements[i] == 0){
      continue;
    }
    distances_to_lighthouses[i] = (distances_to_lighthouses[i]/distance_measurements[i]) - DISTANCE_ANTENA_DELAY_OFFSET;
  }
}

/**
 * @brief Print the full matrix of inter-lighthouse distances.
 *
 * @return void
 */
void Print_Master_All_Distances_Matrix(){
  for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        for (uint8_t j=0;j<NUMBER_OF_LIGHTHOUSES;j++){
            printf("%4f ", master_all_distances_matrix[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Calculate the spatial position of a lighthouse.
 *
 * Selects the appropriate positioning method depending on the lighthouse index.
 *
 * @param lighthouse ID of the lighthouse whose position is calculated.
 * @return void
 */
void Calculate_Position_Of_Lighthouse(uint8_t lighthouse){
  if (lighthouse == 0) {
  }
  else if (lighthouse == 1){
    _set_LGH_1_position();
  }
  else if (lighthouse == 2){
    _set_LGH_2_position();
  }
  else if (lighthouse == 3){
    _set_LGH_3_position();
  }
  else {
    _set_LGH_4plus_position(lighthouse);
  }
}

/**
 * @brief Calculate the position of lighthouse 1.
 *
 * Assumes lighthouse 0 is located at the origin.
 *
 * @return void
 */
void _set_LGH_1_position(){
  float distance = (master_all_distances_matrix[0][1] + master_all_distances_matrix[1][0])/2.0;
  master_all_positions[1].x = distance;
}

/**
 * @brief Calculate the 2D position of lighthouse 2.
 *
 * Uses distances to lighthouse 0 and 1 to estimate X and Y coordinates.
 *
 * @return void
 */
void _set_LGH_2_position(){
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

/**
 * @brief Calculate the 3D position of lighthouse 3.
 *
 * Uses trilateration based on distances to lighthouses 0, 1, and 2.
 *
 * @return void
 */
void _set_LGH_3_position(){
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

/**
 * @brief Calculate the position of lighthouses with index 4 and above.
 *
 * Placeholder for future extensions.
 *
 * @param lighthouse ID of the lighthouse.
 * @return void
 */
void _set_LGH_4plus_position(uint8_t lighthouse){
  // Można rozszerzyć funkcjonalność.
}

/**
 * @brief Print the calculated position of a lighthouse.
 * @param lighthouse ID of the lighthouse.
 * @return void
 */
void Print_Position(uint8_t lighthouse){}