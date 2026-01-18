#include "States.h"

void Reset_Target_Lighthouse_Index(uint8_t* target_lighthouse_index){
    *target_lighthouse_index = LIGHTHOUSE_ID;
    Increment_Target_Lighthouse_Index(target_lighthouse_index);
}

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

void Reset_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = 0;
}

bool Increment_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = (*distance_query_target_index) + 1;
    if (*distance_query_target_index >= NUMBER_OF_LIGHTHOUSES) {
        return true;
    }
    else {
        return false;
    }
}

void Reset_Ack_Target_Index(uint8_t* ack_target_lighthouse, uint8_t* ack_message_index){
    *ack_target_lighthouse = LIGHTHOUSE_ID;
    Increment_Ack_Target_Index(ack_target_lighthouse, ack_message_index);
}

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

bool Validate_Ack_Index_Increase(uint8_t* ack_index){
    *ack_index += 1;
    if (*ack_index >= ACK_MESSAGE_COUNT){
        return false;
    }
    else {
        return true;
    }
}


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