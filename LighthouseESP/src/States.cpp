#include "States.h"

/**
 * @brief Resets the target lighthouse index to the current lighthouse ID
 *        and advances it to the next valid lighthouse.
 *
 * @param target_lighthouse_index Pointer to the lighthouse index to reset.
 */
void Reset_Target_Lighthouse_Index(uint8_t* target_lighthouse_index){
    *target_lighthouse_index = LIGHTHOUSE_ID;
    Increment_Target_Lighthouse_Index(target_lighthouse_index);
}

/**
 * @brief Increments the target lighthouse index and wraps it around
 *        when exceeding the number of lighthouses.
 *
 * @param target_lighthouse_index Pointer to the lighthouse index to increment.
 * @return true if the resulting index equals the current lighthouse ID,
 *         otherwise false.
 */
bool Increment_Target_Lighthouse_Index(uint8_t* target_lighthouse_index){
    *target_lighthouse_index = (*target_lighthouse_index) + 1;
    if ((*target_lighthouse_index) >= NUMBER_OF_LIGHTHOUSES){
        (*target_lighthouse_index) = 0;
    }

    if (*target_lighthouse_index == LIGHTHOUSE_ID){
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Resets the distance query target index to 0.
 *
 * @param distance_query_target_index Pointer to the distance query index to reset.
 */
void Reset_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = 0;
}

/**
 * @brief Increments the distance query target index.
 *
 * @param distance_query_target_index Pointer to the distance query index to increment.
 * @return true if the index reached the maximum number of lighthouses,
 *         otherwise false.
 */
bool Increment_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = (*distance_query_target_index) + 1;
    if (*distance_query_target_index >= NUMBER_OF_LIGHTHOUSES) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Resets the ACK target lighthouse index to the current lighthouse ID
 *        and advances it to the next valid lighthouse.
 *
 * @param ack_target_lighthouse Pointer to the target lighthouse index to reset.
 * @param ack_message_index Pointer to the ACK message index to reset.
 */
void Reset_Ack_Target_Index(uint8_t* ack_target_lighthouse, uint8_t* ack_message_index){
    *ack_target_lighthouse = LIGHTHOUSE_ID;
    Increment_Ack_Target_Index(ack_target_lighthouse, ack_message_index);
}

/**
 * @brief Increments the ACK target lighthouse index and resets the ACK message index.
 *
 * @param ack_target_lighthouse Pointer to the target lighthouse index to increment.
 * @param ack_message_index Pointer to the ACK message index to reset.
 * @return true if the current ACK target lighthouse equals the current lighthouse ID,
 *         otherwise false.
 */
bool Increment_Ack_Target_Index(uint8_t* ack_target_lighthouse, uint8_t* ack_message_index){
    *ack_target_lighthouse = (*ack_target_lighthouse) + 1;
    if (*ack_target_lighthouse >= NUMBER_OF_LIGHTHOUSES){
        *ack_target_lighthouse = 0;
    }
    *ack_message_index = 0;

    if (current_ack_status.target_ack_lighthouse == LIGHTHOUSE_ID){
        return true;
    }
    else {
        return false;
    }
}


/**
 * @brief Validates and increments the ACK message index.
 *
 * @param ack_index Pointer to the ACK index to increment.
 * @return true if the new index is still valid (less than ACK_MESSAGE_COUNT),
 *         otherwise false.
 */
bool Validate_Ack_Index_Increase(uint8_t* ack_index){
    *ack_index += 1;
    if (*ack_index >= ACK_MESSAGE_COUNT){
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Checks if all lighthouses (except the current one) have received
 *        the minimum required distance measurements.
 *
 * @param received_distances Pointer to the array of received distance counts.
 * @return true if all other lighthouses have at least MIN_DISTANCE_MEASUREMENTS,
 *         otherwise false.
 */
bool Check_If_All_Distances_Are_Measured(uint8_t* received_distances){
    uint8_t completed = 0;
    for (uint8_t i=0; i<NUMBER_OF_LIGHTHOUSES;i++){
        if (received_distances[i] >= MIN_DISTANCE_MEASUREMENTS){
            completed++;
        }
    }
    if (completed >= NUMBER_OF_LIGHTHOUSES - 1){
        return true;
    }
    return false;
}