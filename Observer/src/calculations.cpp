#include "calculations.h"

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

void Build_Constant_Matrices(){
    Build_A_Matrix();
    Build_AT_Matrix();
    Build_ATA_Matrix();
    Build_ATA_Inv_Matrix();
    Build_B_Vector_Constants();
}

void Estimate_Position(){
    Build_B_Vector();
    Calculate_ATB_Vector();
    Calculate_Solution();
}

void Update_Distance_To_LGH(uint8_t lgh_index, float new_distance){
    distances_to_lghs[lgh_index] = new_distance;
}

void Update_LGH_Position(uint8_t lgh_index, float x, float y, float z){
    lghs_positions[lgh_index].x = x;
    lghs_positions[lgh_index].y = y;
    lghs_positions[lgh_index].z = z;
}

#pragma region Obliczenia
void Build_A_Matrix(){
    float x1 = lghs_positions[0].x, y1 = lghs_positions[0].y, z1 = lghs_positions[0].z;
    for (uint8_t row=0; row<NUMBER_OF_LIGHTHOUSES-1; row++){
        float xj = lghs_positions[row+1].x, yj = lghs_positions[row+1].y, zj = lghs_positions[row+1].z;
        A_matrix[row][0] = -2.0 * xj + 2.0 * x1;
        A_matrix[row][1] = -2.0 * yj + 2.0 * y1;
        A_matrix[row][2] = -2.0 * zj + 2.0 * z1;
    }
}

void Build_AT_Matrix(){
    for (uint8_t row=0; row<NUMBER_OF_LIGHTHOUSES-1; row++){
        for (uint8_t column=0; column<3; column++){
            AT_matrix[column][row] = A_matrix[row][column];
        }
    }
}

void Build_ATA_Matrix(){
    for (uint8_t i = 0; i < 3; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            ATA_matrix[i][j] = 0.0;

            for (uint8_t k = 0; k < NUMBER_OF_LIGHTHOUSES-1; k++) {
                ATA_matrix[i][j] += AT_matrix[i][k] * A_matrix[k][j];
            }
        }
    }
}

uint8_t Build_ATA_Inv_Matrix() {
    uint8_t i, j, k;
    float ratio;

    // Augmented matrix [M | I]
    float aug[3][2 * 3];

    // Initialize augmented matrix
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            aug[i][j] = ATA_matrix[i][j];
            aug[i][j + 3] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan elimination
    for (i = 0; i < 3; i++) {
        if (aug[i][i] == 0.0)
            return 1; // Singular matrix

        for (j = 0; j < 3; j++) {
            if (i != j) {
                ratio = aug[j][i] / aug[i][i];
                for (k = 0; k < 2 * 3; k++) {
                    aug[j][k] -= ratio * aug[i][k];
                }
            }
        }
    }

    // Normalize diagonal elements to 1
    for (i = 0; i < 3; i++) {
        double diag = aug[i][i];
        for (j = 0; j < 2 * 3; j++) {
            aug[i][j] /= diag;
        }
    }

    // Extract inverse matrix
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ATA_inv_matrix[i][j] = aug[i][j + 3];
        }
    }

    return 0;
}

void Build_B_Vector_Constants(){
    for (uint8_t j=0; j<NUMBER_OF_LIGHTHOUSES; j++){
        B_vector_constants[j] = -(lghs_positions[j].x)*(lghs_positions[j].x)
                            - (lghs_positions[j].y)*(lghs_positions[j].y) - (lghs_positions[j].z)*(lghs_positions[j].z);
    }
}

void Build_B_Vector(){
    for (uint8_t j=0; j<NUMBER_OF_LIGHTHOUSES-1; j++){
        B_vector[j] = (distances_to_lghs[j+1])*(distances_to_lghs[j+1])
         - (distances_to_lghs[0])*(distances_to_lghs[0])
         + B_vector_constants[j+1] - B_vector_constants[0];

        }
}

void Calculate_ATB_Vector(){
    uint8_t i, j;
    for (i = 0; i < 3; i++) {
        ATB_vector[i] = 0.0;
        for (j = 0; j < NUMBER_OF_LIGHTHOUSES-1; j++) {
            ATB_vector[i] += AT_matrix[i][j] * B_vector[j];
        }
    }
}

void Calculate_Solution(){
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
#pragma endregion