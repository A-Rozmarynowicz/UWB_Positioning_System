#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "LighthouseConfig.h"

struct StateData {
  bool ignoring_sent_callbacks;
  uint8_t target_lighthouse;
  uint8_t distance_query_target;
  uint8_t stored_next_state;
  uint16_t time_measurements_completed;
  uint16_t message_index;
  uint32_t last_registered_time;
  double elapsed_times_sum;
  double stored_targets_avg_response_time;
};

extern struct StateData current_state_data;
extern uint8_t completed_distance_measurements[NUMBER_OF_LIGHTHOUSES];

enum States {
  INITIAL = 0,
  UWB_QUERY, // 1
  UWB_RESPONSE, // 2
  POST_UWB_CHECK_IF_ALL_LGHS_SET, // 3
  RELAY_UWB_QUERING, // 4
  INFORM_END_CONFIG, // 5
  DISTANCE_MEASURE_RESPONSE, // 6
  DISTANCE_MEASURE_QUERY, // 7
  SEND_CALCULATED_POSITION, // 8
  OBSERVER_RESPONSE, // 9
};

enum State_Machine_Errors {
  INEXISTING_STATE,
  WRONG_TRANSITION,
};

const uint16_t UWB_COUNT = 20;
const uint8_t MESSAGE_MAX_COUNT = 5;

extern States current_state;

void Reset_And_Initialize_Machine();
void State_Machine_Error(State_Machine_Errors error);

void Change_State(States new_state);
void State_Enter();
void State_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void State_SentCallback(uint32_t send_time);
void State_TimerCallback(Timer_Callbacks timer_callback);
void State_Button_Callback(uint8_t button);
void State_UWB_New_Range(uint16_t device, float range, float rx_power);
void State_Exit();

void Initial_Enter();
void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Initial_SentCallback(uint32_t send_time);
void Initial_TimerCallback(Timer_Callbacks timer_callback);
void Initial_ButtonCallback(uint8_t button);
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power);
void Initial_Exit();

void UWB_Query_Enter();
void UWB_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void UWB_Query_SentCallback(uint32_t send_time);
void UWB_Query_TimerCallback(Timer_Callbacks timer_callback);
void UWB_Query_ButtonCallback(uint8_t button);
void UWB_Query_UWB_New_Range(uint16_t device, float range, float rx_power);
void UWB_Query_Exit();

void UWB_Response_Enter();
void UWB_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void UWB_Response_SentCallback(uint32_t send_time);
void UWB_Response_TimerCallback(Timer_Callbacks timer_callback);
void UWB_Response_ButtonCallback(uint8_t button);
void UWB_Response_UWB_New_Range(uint16_t device, float range, float rx_power);
void UWB_Response_Exit();

void Post_UWB_Check_If_All_LGHS_Set_Enter();
void Post_UWB_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Post_UWB_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time);
void Post_UWB_Check_If_All_LGHS_Set_TimerCallback(Timer_Callbacks timer_callback);
void Post_UWB_Check_If_All_LGHS_Set_ButtonCallback(uint8_t button);
void Post_UWB_Check_If_All_LGHS_Set_UWB_New_Range(uint16_t device, float range, float rx_power);
void Post_UWB_Check_If_All_LGHS_Set_Exit();

void Relay_UWB_Quering_Enter();
void Relay_UWB_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Relay_UWB_Quering_SentCallback(uint32_t send_time);
void Relay_UWB_Quering_TimerCallback(Timer_Callbacks timer_callback);
void Relay_UWB_Quering_ButtonCallback(uint8_t button);
void Relay_UWB_Quering_UWB_New_Range(uint16_t device, float range, float rx_power);
void Relay_UWB_Quering_Exit();

void Inform_End_Config_Enter();
void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Inform_End_Config_SentCallback(uint32_t send_time);
void Inform_End_Config_TimerCallback(Timer_Callbacks timer_callback);
void Inform_End_Config_ButtonCallback(uint8_t button);
void Inform_End_Config_UWB_New_Range(uint16_t device, float range, float rx_power);
void Inform_End_Config_Exit();

void Distance_Measure_Response_Enter();
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Distance_Measure_Response_SentCallback(uint32_t send_time);
void Distance_Measure_Response_TimerCallback(Timer_Callbacks timer_callback);
void Distance_Measure_Response_ButtonCallback(uint8_t button);
void Distance_Measure_Response_UWB_New_Range(uint16_t device, float range, float rx_power);
void Distance_Measure_Response_Exit();

void Distance_Measure_Query_Enter();
void Distance_Measure_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Distance_Measure_Query_SentCallback(uint32_t send_time);
void Distance_Measure_Query_TimerCallback(Timer_Callbacks timer_callback);
void Distance_Measure_Query_ButtonCallback(uint8_t button);
void Distance_Measure_Query_UWB_New_Range(uint16_t device, float range, float rx_power);
void Distance_Measure_Query_Exit();

void Send_Calculated_Position_Enter();
void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Send_Calculated_Position_SentCallback(uint32_t send_time);
void Send_Calculated_Position_TimerCallback(Timer_Callbacks timer_callback);
void Send_Calculated_Position_ButtonCallback(uint8_t button);
void Send_Calculated_Position_UWB_New_Range(uint16_t device, float range, float rx_power);
void Send_Calculated_Position_Exit();

void Observer_Response_Enter();
void Observer_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time);
void Observer_Response_SentCallback(uint32_t send_time);
void Observer_Response_TimerCallback(Timer_Callbacks timer_callback);
void Observer_Response_ButtonCallback(uint8_t button);
void Observer_Response_UWB_New_Range(uint16_t device, float range, float rx_power);
void Observer_Response_Exit();

#endif