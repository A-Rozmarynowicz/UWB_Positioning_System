#include "States.h"

void Handle_Sending_Burst_Query_Message(){
    current_state_data.message_index += 1;
    if (current_state_data.message_index >= BURST_COUNT){
        Change_State(STATES::POST_BURST_CHECK_IF_ALL_LGHS_SET);
        return;
    }
    MESSAGES::Send_Burst_Query(current_state_data.target_lighthouse);
    // Serial.printf("Packet index: %d\n", current_state_data.message_index);
}

uint8_t Get_New_State_From_Post_Burst(uint8_t current_target_lighthouse) {
    if (current_target_lighthouse == LIGHTHOUSE_ID){
        if (LIGHTHOUSE_ID == NUMBER_OF_LIGHTHOUSES - 1){
            return STATES::INFORM_END_CONFIG;
        }
        else {
            return STATES::RELAY_BURST_QUERING;
        }
    }
    else {
        return STATES::BURST_QUERY;
    }
}

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

double Calculate_Avg_Response_Time(double time_responses_sum, uint16_t completed_measurements){
    double avg = (time_responses_sum)/((double) completed_measurements);
    return avg;
}

bool Handle_Post_Burst_State_Change(uint8_t* current_target_lighthouse){
    Increment_Target_Lighthouse_Index(current_target_lighthouse);
    STATES new_state = static_cast<STATES>(Get_New_State_From_Post_Burst(*current_target_lighthouse));
    switch (new_state) {
        case STATES::BURST_QUERY:
            Change_State(STATES::BURST_QUERY);
            break;
        case STATES::RELAY_BURST_QUERING:
            Change_State(STATES::RELAY_BURST_QUERING);
            break;
        case STATES::INFORM_END_CONFIG:
            Change_State(STATES::INFORM_END_CONFIG);
            break;
        default:
            return false;
    }
    return true;
}