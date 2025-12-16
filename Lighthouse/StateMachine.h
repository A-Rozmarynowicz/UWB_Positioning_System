#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "LighthouseConfig.h"
#include "Timing.h"
#include "Communication.h"


enum STATES {
  INITIAL = 0,
  BURST_QUERY, // 1
  BURST_RESPONSE, // 2
  POST_BURST_CHECK_IF_ALL_LGHS_SET, // 3
  RELAY_BURST_QUERING, // 4
  INFORM_END_CONFIG, // 5
  DISTANCE_MEASURE_RESPONSE, // 6
  DISTANCE_MEASURE_QUERY, // 7
  SEND_CALCULATED_POSITION, // 8
  SAILOR_RESPONSE, // 9
};

enum STATE_MACHINE_ERRORS {
  INEXISTING_STATE,
};


const uint8_t BURST_COUNT = 10; 

extern STATES current_state;
extern uint8_t burst_index;

void Reset_And_Initialize_Machine();
void State_Machine_Error(STATE_MACHINE_ERRORS error);

void Change_State(STATES new_state);
void State_Enter();
void State_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void State_SentCallback(uint32_t send_time);
void State_TimerCallback();
void State_Exit();

void Initial_Enter();
void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Initial_SentCallback(uint32_t send_time);
void Initial_TimerCallback();
void Initial_Exit();

void Burst_Query_Enter();
void Burst_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Burst_Query_SentCallback(uint32_t send_time);
void Burst_Query_TimerCallback();
void Burst_Query_Exit();

void Burst_Response_Enter();
void Burst_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Burst_Response_SentCallback(uint32_t send_time);
void Burst_Response_TimerCallback();
void Burst_Response_Exit();

void Post_Burst_Check_If_All_LGHS_Set_Enter();
void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Post_Burst_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time);
void Post_Burst_Check_If_All_LGHS_Set_TimerCallback();
void Post_Burst_Check_If_All_LGHS_Set_Exit();

void Relay_Burst_Quering_Enter();
void Relay_Burst_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Relay_Burst_Quering_SentCallback(uint32_t send_time);
void Relay_Burst_Quering_TimerCallback();
void Relay_Burst_Quering_Exit();

void Inform_End_Config_Enter();
void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Inform_End_Config_SentCallback(uint32_t send_time);
void Inform_End_Config_TimerCallback();
void Inform_End_Config_Exit();

void Distance_Measure_Response_Enter();
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Distance_Measure_Response_SentCallback(uint32_t send_time);
void Distance_Measure_Response_TimerCallback();
void Distance_Measure_Response_Exit();

void Distance_Measure_Query_Enter();
void Distance_Measure_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Distance_Measure_Query_SentCallback(uint32_t send_time);
void Distance_Measure_Query_TimerCallback();
void Distance_Measure_Query_Exit();

void Send_Calculated_Position_Enter();
void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Send_Calculated_Position_SentCallback(uint32_t send_time);
void Send_Calculated_Position_TimerCallback();
void Send_Calculated_Position_Exit();

void Sailor_Response_Enter();
void Sailor_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Sailor_Response_SentCallback(uint32_t send_time);
void Sailor_Response_TimerCallback();
void Sailor_Response_Exit();


#endif