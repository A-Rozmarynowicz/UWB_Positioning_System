#include "state_machine.h"
#include "states_functions.h"
#include "string.h"

#pragma region Initial State Functions
void Initial_Enter(){}
void Initial_ReceiveCallback(const uint8_t* data, int dataLen){
    if (data[Data_Setup::COMMAND] == Data_Commands::READY_FOR_OBSERVER){
        Change_State(States::QUERY_POSITIONS);
    }
    if (data[Data_Setup::COMMAND] == Data_Commands::CHANGE_STATE_COM){
        Serial.printf("Someone: %d wants to change state to %d\n", data[Data_Setup::TRANSMITTER_ID], data[Data_Setup::SINGLE_0]);
    }
}
void Initial_SentCallback(){}
void Initial_TimerCallback(Timer_Callbacks timer_callback){}
void Initial_SailorCommand(Sailor_Commands command){}
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power){}
void Initial_Exit(){}
#pragma endregion

#pragma region Query Positions State Functions
void Query_Positions_Enter(){
    UWB_Exchange_Successful();
    MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    Serial.printf("Sent pos query\n");
    Start_Ack_Timer();
}

void Query_Positions_ReceiveCallback(const uint8_t* data, int dataLen){
    Serial.printf("dataLen: %d\n", dataLen);
    if (data[Data_Setup::COMMAND] == Data_Commands::OBSERVER_RESPONSE_POSITION) {
        Serial.printf("Received observer response\n");
        if (data[Data_Setup::TRANSMITTER_ID] != current_state_data.target_lgh) {
            Serial.printf("Wrong pos query transmitter: actual: %d vs desired: %d\n", data[Data_Setup::TRANSMITTER_ID], current_state_data.target_lgh);
            return;
        }
        Stop_Ack_Timer();
        Serial.printf("Po stop ack timer\n");
        current_state_data.ack_index = 0;
        float x, y, z;
        memcpy(&x, &(data[Data_Setup::QUAD_0]), sizeof(float));
        memcpy(&y, &(data[Data_Setup::QUAD_1]), sizeof(float));
        memcpy(&z, &(data[Data_Setup::QUAD_2]), sizeof(float));
        Serial.printf("Po MEMCPY quad pos\n");
        Update_LGH_Position(current_state_data.target_lgh, x, y, z);
        Increment_Target_LGH(&current_state_data.target_lgh);
        if (current_state_data.target_lgh == 0){
            Change_State(States::QUERY_DISTANCES);
            return;
        }
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
        Start_Ack_Timer();
        Serial.printf("Sent pos query\n");
    }
}

void Query_Positions_SentCallback(){}

void Query_Positions_TimerCallback(Timer_Callbacks timer_callback){
    Serial.printf("Timer cllabsck\n");
    current_state_data.ack_index += 1;
    if (current_state_data.ack_index >= MAX_ACK_NUMBER){
        Serial.printf("ALL acks missed for pos query\n");
        current_state_data.ack_index = 0;
        Increment_Target_LGH(&current_state_data.target_lgh);
        if (current_state_data.target_lgh == 0){
            Change_State(States::QUERY_DISTANCES);
            return;
        }
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    }
    else {
        Serial.printf("Missed a single position response \n");
        MESSAGES::Send_Query_Position(current_state_data.target_lgh);
    }
}

void Query_Positions_SailorCommand(Sailor_Commands command){}

void Query_Positions_UWB_New_Range(uint16_t device, float range, float rx_power){}

void Query_Positions_Exit(){
    Build_Constant_Matrices();
}
#pragma endregion

#pragma region Query Distances State Functions
void Query_Distances_Enter(){
    Enable_UWB();
    UWB_Exchange_Successful();
}

void Query_Distances_ReceiveCallback(const uint8_t* data, int dataLen){}
void Query_Distances_SentCallback(){}
void Query_Distances_TimerCallback(Timer_Callbacks timer_callback){}
void Query_Distances_SailorCommand(Sailor_Commands command){}

void Query_Distances_UWB_New_Range(uint16_t device, float range, float rx_power){
    int lgh_index = Get_LGH_From_Short_Address(device);
    if (lgh_index < 0){
        Serial.printf("NOT FOUND LGH INDEX\n");
        return;
    }
    UWB_Exchange_Successful();
    Update_Distance_To_LGH(lgh_index, range);
    if (Are_Enough_Measurements_Complete()) {
        Serial.printf("ENOUGH\n");
        Estimate_Position();
        Send_Current_Position(&current_position);
    }
    else {
        for (int i = 0; i < NUMBER_OF_LIGHTHOUSES;i++){
            Serial.printf("%d->%0.2f   ", i, distances_to_lghs[i]);
        }
        Serial.printf("\n");
    }
}
void Query_Distances_Exit(){}
#pragma endregion
