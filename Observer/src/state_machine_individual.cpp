#include "state_machine.h"
#include "states_functions.h"
#include "string.h"

#pragma region Initial State Functions
void Initial_Enter(){}
void Initial_ReceiveCallback(const uint8_t* data, int dataLen){
    if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::READY_FOR_SAILOR){
        Change_State(STATES::QUERY_POSITIONS);
    }
}
void Initial_SentCallback(){}
void Initial_TimerCallback(TIMER_CALLBACKS timer_callback){}
void Initial_SailorCommand(SAILOR_COMMANDS command){}
void Initial_UWB_Info(){}
void Initial_Exit(){}
#pragma endregion

#pragma region Query Positions State Functions
void Query_Positions_Enter(){
    MESSAGES::Send_Query_Position(current_state_data.target_lgh);
}

void Query_Positions_ReceiveCallback(const uint8_t* data, int dataLen){
    if (data[DATA_SETUP::COMMAND] == DATA_COMMANDS::OBSERVER_RESPONSE_POSITION) {
        Stop_Ack_Timer();
        if (data[DATA_SETUP::TRANSMITTER_ID] != current_state_data.target_lgh) {
            Serial.printf("Wrong pos query transmitter: actual: %d vs desired: %d\n", data[DATA_SETUP::TRANSMITTER_ID], current_state_data.target_lgh);
            MESSAGES::Send_Query_Position(current_state_data.target_lgh);
            return;
        }
        current_state_data.ack_index = 0;
        float x, y, z;
        memcpy(&x, &(data[DATA_SETUP::QUAD_0]), sizeof(float));
        memcpy(&y, &(data[DATA_SETUP::QUAD_1]), sizeof(float));
        memcpy(&z, &(data[DATA_SETUP::QUAD_2]), sizeof(float));
        Update_LGH_Position(current_state_data.target_lgh, x, y, z);
        Increment_Target_LGH(&current_state_data.target_lgh);
        if (current_state_data.target_lgh == 0){
            Change_State(STATES::QUERY_DISTANCES);
            return;
        }
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    }
}

void Query_Positions_SentCallback(){}

void Query_Positions_TimerCallback(TIMER_CALLBACKS timer_callback){
    current_state_data.ack_index += 1;
    if (current_state_data.ack_index >= MAX_ACK_NUMBER){
        Serial.printf("ALL acks missed for pos query\n");
        current_state_data.ack_index = 0;
        Increment_Target_LGH(&current_state_data.target_lgh);
        if (current_state_data.target_lgh == 0){
            Change_State(STATES::QUERY_DISTANCES);
            return;
        }
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    }
    else {
        Serial.printf("Missed a single position response \n");
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    }
}

void Query_Positions_SailorCommand(SAILOR_COMMANDS command){}
void Query_Positions_UWB_Info(){}
void Query_Positions_Exit(){}
#pragma endregion

#pragma region Query Distances State Functions
void Query_Distances_Enter(){
    current_state_data.target_lgh = 0;
    current_state_data.ack_index = 0;
}

void Query_Distances_ReceiveCallback(const uint8_t* data, int dataLen){}
void Query_Distances_SentCallback(){}
void Query_Distances_TimerCallback(TIMER_CALLBACKS timer_callback){}
void Query_Distances_SailorCommand(SAILOR_COMMANDS command){}
void Query_Distances_UWB_Info(){}
void Query_Distances_Exit(){}
#pragma endregion
