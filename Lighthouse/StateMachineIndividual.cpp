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
void Initial_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Initial_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Initial_TimerCallback(){};
void Initial_Exit(){};
#pragma endregion

#pragma region Burst Query State Functions
void Burst_Query_Enter(){
  Serial.println("Starting Response TImer.");
  Start_Response_Await_Timer();
};
void Burst_Query_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Burst_Query_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Burst_Query_TimerCallback(){};
void Burst_Query_Exit(){};
#pragma endregion

#pragma region Burst Response State Functions
void Burst_Response_Enter(){};
void Burst_Response_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Burst_Response_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Burst_Response_TimerCallback(){};
void Burst_Response_Exit(){};
#pragma endregion

#pragma region Post Burst Check If All LGHS Set State Functions
void Post_Burst_Check_If_All_LGHS_Set_Enter(){};
void Post_Burst_Check_If_All_LGHS_Set_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Post_Burst_Check_If_All_LGHS_Set_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Post_Burst_Check_If_All_LGHS_Set_TimerCallback(){};
void Post_Burst_Check_If_All_LGHS_Set_Exit(){};
#pragma endregion

#pragma region Relay Burst Quering State Functions
void Relay_Burst_Quering_Enter(){};
void Relay_Burst_Quering_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Relay_Burst_Quering_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Relay_Burst_Quering_TimerCallback(){};
void Relay_Burst_Quering_Exit(){};
#pragma endregion

#pragma region Inform End Config State Functions
void Inform_End_Config_Enter(){};
void Inform_End_Config_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Inform_End_Config_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Inform_End_Config_TimerCallback(){};
void Inform_End_Config_Exit(){};
#pragma endregion

#pragma region Distance Measure Response State Functions
void Distance_Measure_Response_Enter(){};
void Distance_Measure_Response_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Distance_Measure_Response_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Distance_Measure_Response_TimerCallback(){};
void Distance_Measure_Response_Exit(){};
#pragma endregion

#pragma region Distance Measure Query State Functions
void Distance_Measure_Query_Enter(){};
void Distance_Measure_Query_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Distance_Measure_Query_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Distance_Measure_Query_TimerCallback(){};
void Distance_Measure_Query_Exit(){};
#pragma endregion

#pragma region Send Calculated Position State Functions
void Send_Calculated_Position_Enter(){};
void Send_Calculated_Position_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Send_Calculated_Position_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Send_Calculated_Position_TimerCallback(){};
void Send_Calculated_Position_Exit(){};
#pragma endregion

#pragma region Sailor Response State Functions
void Sailor_Response_Enter(){};
void Sailor_Response_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen){};
void Sailor_Response_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status){};
void Sailor_Response_TimerCallback(){};
void Sailor_Response_Exit(){};
#pragma endregion
