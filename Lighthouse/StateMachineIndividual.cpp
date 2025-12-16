#include "StateMachine.h"

#pragma region Initial State Functions
void Initial_Enter(){
  if (LIGHTHOUSE_ID == 0){
    Change_State(STATES::BURST_QUERY);
  }
  else {
    Change_State(STATES::BURST_RESPONSE);
  }
};
void Initial_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Initial_SentCallback(uint32_t send_time){};
void Initial_TimerCallback(){};
void Initial_Exit(){};
#pragma endregion

#pragma region Burst Query State Functions
void Burst_Query_Enter(){
  Serial.println("Starting Response TImer.");
  Start_Response_Await_Timer();
};
void Burst_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Burst_Query_SentCallback(uint32_t send_time){};
void Burst_Query_TimerCallback(){};
void Burst_Query_Exit(){};
#pragma endregion

#pragma region Burst Response State Functions
void Burst_Response_Enter(){};
void Burst_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Burst_Response_SentCallback(uint32_t send_time){};
void Burst_Response_TimerCallback(){};
void Burst_Response_Exit(){};
#pragma endregion

#pragma region Post Burst Check If All LGHS Set State Functions
void Post_Burst_Check_If_All_LGHS_Set_Enter(){};
void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Post_Burst_Check_If_All_LGHS_Set_SentCallback(uint32_t send_time){};
void Post_Burst_Check_If_All_LGHS_Set_TimerCallback(){};
void Post_Burst_Check_If_All_LGHS_Set_Exit(){};
#pragma endregion

#pragma region Relay Burst Quering State Functions
void Relay_Burst_Quering_Enter(){};
void Relay_Burst_Quering_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Relay_Burst_Quering_SentCallback(uint32_t send_time){};
void Relay_Burst_Quering_TimerCallback(){};
void Relay_Burst_Quering_Exit(){};
#pragma endregion

#pragma region Inform End Config State Functions
void Inform_End_Config_Enter(){};
void Inform_End_Config_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Inform_End_Config_SentCallback(uint32_t send_time){};
void Inform_End_Config_TimerCallback(){};
void Inform_End_Config_Exit(){};
#pragma endregion

#pragma region Distance Measure Response State Functions
void Distance_Measure_Response_Enter(){};
void Distance_Measure_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Distance_Measure_Response_SentCallback(uint32_t send_time){};
void Distance_Measure_Response_TimerCallback(){};
void Distance_Measure_Response_Exit(){};
#pragma endregion

#pragma region Distance Measure Query State Functions
void Distance_Measure_Query_Enter(){};
void Distance_Measure_Query_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Distance_Measure_Query_SentCallback(uint32_t send_time){};
void Distance_Measure_Query_TimerCallback(){};
void Distance_Measure_Query_Exit(){};
#pragma endregion

#pragma region Send Calculated Position State Functions
void Send_Calculated_Position_Enter(){};
void Send_Calculated_Position_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Send_Calculated_Position_SentCallback(uint32_t send_time){};
void Send_Calculated_Position_TimerCallback(){};
void Send_Calculated_Position_Exit(){};
#pragma endregion

#pragma region Sailor Response State Functions
void Sailor_Response_Enter(){};
void Sailor_Response_ReceiveCallback(const uint8_t* data, int dataLen, uint32_t receive_time){};
void Sailor_Response_SentCallback(uint32_t send_time){};
void Sailor_Response_TimerCallback(){};
void Sailor_Response_Exit(){};
#pragma endregion
