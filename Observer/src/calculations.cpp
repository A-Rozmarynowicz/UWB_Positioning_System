#include "calculations.h"

uint16_t distances_measurements_completed[NUMBER_OF_LIGHTHOUSES] = {0};
float distances_to_lghs[NUMBER_OF_LIGHTHOUSES] = {0};
Position lghs_positions[NUMBER_OF_LIGHTHOUSES] = {0};
Position current_position = {0};

float B_vector_constants[NUMBER_OF_LIGHTHOUSES] = {0};

float A_matrix[NUMBER_OF_LIGHTHOUSES-1][3] = {0};
float AT_matrix[3][NUMBER_OF_LIGHTHOUSES-1] = {0};
float ATA_matrix[3][3] = {0};
float ATA_inv_matrix[3][3] = {0};
float B_vector[NUMBER_OF_LIGHTHOUSES-1] = {0};
float ATB_vector[3] = {0};
float solution_vector[3] = {0};

// Public

/**
 * @brief Build constant matrices used for position estimation.
 *
 * @details
 * Creates matrices A, Aᵀ, AᵀA and its inverse, as well as constants for B vector
 * based on lighthouse positions. This is required before running position
 * estimation.
 */
void Build_Constant_Matrices(){
    _build_a_matrix();
    _build_at_matrix();
    _build_ata_matrix();
    if (_build_ata_inv_matrix() == 1){
        Calculations_Error();
        return;
    }
    _build_b_vector_constants();
}

/**
 * @brief Estimate current position using least squares method.
 *
 * @details
 * Averages measurements, builds B vector, computes AᵀB, solves for position
 * and resets measurement buffers.
 */
void Estimate_Position(){
    _average_results();
    _build_b_vector();
    _calculate_atb_vector();
    _calculate_solution();
    _flush_distance_measurements();
}

/**
 * @brief Update accumulated distance measurement for a lighthouse.
 *
 * @param lgh_index Index of the lighthouse.
 * @param new_distance Newly measured distance value.
 *
 * @details
 * Adds the distance to the running sum and increments the measurement counter,
 * if it is within allowed limits.
 */
void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance){
    if (distances_measurements_completed[lgh_index] > MAXIMUM_MEASUREMENT_PER_LGH){
        return;
    }
    if (new_distance > THEORETICAL_MAX_DISTANCE || new_distance < 0.0f){
        return;
    }
    distances_to_lghs[lgh_index] += new_distance;
    distances_measurements_completed[lgh_index] += 1;
}

/**
 * @brief Get lighthouse index from UWB short address.
 *
 * @param short_address UWB short address.
 * @return Index of the lighthouse, or -1 if not found.
 */
int8_t Get_LGH_From_Short_Address(const uint16_t short_address){
    for (uint8_t i=0;i<NUMBER_OF_LIGHTHOUSES;i++){
        const uint8_t* potential_address = uwb_addresses_from_LGH[i];
        if (Get_Short_Address_From_Long(potential_address) == short_address){
            return i;
        }
    }
    return -1;
}

/**
 * @brief Convert long UWB address to short address.
 *
 * @param address Pointer to long address array.
 * @return Short address (first two bytes).
 */
uint16_t Get_Short_Address_From_Long(const uint8_t* address){
    uint16_t short_address = address[1]*256 + address[0];
    return short_address;
}

/**
 * @brief Update lighthouse position coordinates.
 *
 * @param lgh_index Index of the lighthouse.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @param z Z coordinate.
 */
void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z){
    lghs_positions[lgh_index].x = x;
    lghs_positions[lgh_index].y = y;
    lghs_positions[lgh_index].z = z;
}

/**
 * @brief Check if minimum number of measurements is complete for all lighthouses.
 *
 * @return True if all lighthouses have enough measurements, false otherwise.
 */
bool Are_Enough_Measurements_Complete() {
    for (int i = 0; i < NUMBER_OF_LIGHTHOUSES; i++) {
        if  (distances_measurements_completed[i] < MINIMUM_MEASUREMENTS_PER_LGH){
            return false;
        }
    }
    return true;
}

/**
 * @brief Handle calculation errors.
 *
 * @details
 * Called when matrix inversion fails or other calculation errors occur.
 * Turns on the error LED and logs an error message.
 */
void Calculations_Error() {
    Serial.printf("CALCULATION ERRROE\n");
    Error_LED_On();
}

// Private
#pragma region Calculations

/**
 * @brief Build matrix A for position estimation.
 */
void _build_a_matrix(){
    float x1 = lghs_positions[0].x, y1 = lghs_positions[0].y, z1 = lghs_positions[0].z;
    for (uint8_t row=0; row<NUMBER_OF_LIGHTHOUSES-1; row++){
        float xj = lghs_positions[row+1].x, yj = lghs_positions[row+1].y, zj = lghs_positions[row+1].z;
        A_matrix[row][0] = -2.0 * xj + 2.0 * x1;
        A_matrix[row][1] = -2.0 * yj + 2.0 * y1;
        A_matrix[row][2] = -2.0 * zj + 2.0 * z1;
    }
}

/**
 * @brief Build matrix Aᵀ (transpose of A).
 */
void _build_at_matrix(){
    for (uint8_t row=0; row<NUMBER_OF_LIGHTHOUSES-1; row++){
        for (uint8_t column=0; column<3; column++){
            AT_matrix[column][row] = A_matrix[row][column];
        }
    }
}

/**
 * @brief Build matrix AᵀA.
 */
void _build_ata_matrix(){
    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            ATA_matrix[i][j] = 0.0;

            for (uint8_t k = 0; k < NUMBER_OF_LIGHTHOUSES-1; k++) {
                ATA_matrix[i][j] += AT_matrix[i][k] * A_matrix[k][j];
            }
        }
    }
}

/**
 * @brief Invert matrix AᵀA using Gauss-Jordan elimination.
 *
 * @return 0 on success, 1 if matrix is singular.
 */
uint8_t _build_ata_inv_matrix() {
    // Nie ma sensu tego rozbijać na oddzielne funkcje.
    uint8_t i, j, k;
    float ratio;

    float aug[3][2 * 3];

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            aug[i][j] = ATA_matrix[i][j];
            aug[i][j + 3] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (i = 0; i < 3; i++) {
        if (aug[i][i] == 0.0)
            return 1;

        for (j = 0; j < 3; j++) {
            if (i != j) {
                ratio = aug[j][i] / aug[i][i];
                for (k = 0; k < 2 * 3; k++) {
                    aug[j][k] -= ratio * aug[i][k];
                }
            }
        }
    }

    for (i = 0; i < 3; i++) {
        double diag = aug[i][i];
        for (j = 0; j < 2 * 3; j++) {
            aug[i][j] /= diag;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ATA_inv_matrix[i][j] = aug[i][j + 3];
        }
    }

    return 0;
}

/**
 * @brief Build constants for B vector from lighthouse positions.
 */
void _build_b_vector_constants(){
    for (uint8_t j=0; j<NUMBER_OF_LIGHTHOUSES; j++){
        B_vector_constants[j] = -(lghs_positions[j].x)*(lghs_positions[j].x)
                            - (lghs_positions[j].y)*(lghs_positions[j].y) - (lghs_positions[j].z)*(lghs_positions[j].z);
    }
}

/**
 * @brief Build vector B based on averaged distances.
 */
void _build_b_vector(){
    for (uint8_t j=0; j<NUMBER_OF_LIGHTHOUSES-1; j++){
        B_vector[j] = (distances_to_lghs[j+1])*(distances_to_lghs[j+1])
         - (distances_to_lghs[0])*(distances_to_lghs[0])
         + B_vector_constants[j+1] - B_vector_constants[0];

        }
}

/**
 * @brief Compute vector AᵀB.
 */
void _calculate_atb_vector(){
    uint8_t i, j;
    for (i = 0; i < 3; i++) {
        ATB_vector[i] = 0.0;
        for (j = 0; j < NUMBER_OF_LIGHTHOUSES-1; j++) {
            ATB_vector[i] += AT_matrix[i][j] * B_vector[j];
        }
    }
}

/**
 * @brief Solve for position vector using (AᵀA)⁻¹AᵀB.
 */
void _calculate_solution(){
    uint8_t i, j;
    Serial.printf("Solution\n");
    for (i = 0; i < 3; i++) {
        solution_vector[i] = 0.0;
        for (j = 0; j < 3; j++) {
            solution_vector[i] += ATA_inv_matrix[i][j] * ATB_vector[j];
        }
        Serial.printf("%.2f\n", solution_vector[i]);
    }
    current_position.x = solution_vector[0];
    current_position.y = solution_vector[1];
    current_position.z = solution_vector[2];
}

/**
 * @brief Average measured distances for each lighthouse.
 */
void _average_results() {
    for (int i = 0; i < NUMBER_OF_LIGHTHOUSES; i++) {
        if (distances_measurements_completed[i] == 0){
            continue;
        }
        distances_to_lghs[i] /= distances_measurements_completed[i];
    }
}

/**
 * @brief Reset measurement buffers after position calculation.
 */
void _flush_distance_measurements(){
    for (int i = 0; i < NUMBER_OF_LIGHTHOUSES; i++) {
        distances_measurements_completed[i] = 0;
        distances_to_lghs[i] = 0.0f;
    }
}


#pragma endregion