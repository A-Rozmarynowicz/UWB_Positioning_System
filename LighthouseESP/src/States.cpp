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

void Increment_Target_Lighthouse_Index(uint8_t* target_lighthouse_index){
    uint8_t new_index= (*target_lighthouse_index) + 1;
    if (new_index >= NUMBER_OF_LIGHTHOUSES){
        new_index = 0;
    }
    *target_lighthouse_index = new_index;
}

void Reset_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = 0;
}

void Increment_Distance_Query_Target_Index(uint8_t* distance_query_target_index){
    *distance_query_target_index = (*distance_query_target_index) + 1;
}

double Calculate_Avg_Response_Time(double time_responses_sum, uint16_t completed_measurements){
    double avg = (time_responses_sum)/((double) completed_measurements);
    return avg;
}
