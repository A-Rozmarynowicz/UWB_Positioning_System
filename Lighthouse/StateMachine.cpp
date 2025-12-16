#include "StateMachine.h"

#pragma region MACHINE
void Change_State(StateMachine::STATES new_state){
  State_Exit();
  current_state = new_state;
  State_Enter();
}
void State_Enter(){
  switch (current_state) {
    case StateMachine::STATES::INITIAL_STATE:
      InitialState_Enter();
      break;
  }
};
void State_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void State_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status);
void State_TimerCallback();
void State_Exit();
#pragma endregion

#pragma region INITIAL_STATE
void InitialState_Enter(){
  if (LIGHTHOUSE_ID == 0){
    Change_State(StateMachine::STATES::BURST_QUERY_STATE);
  }
  else {
    Change_State(StateMachine::STATES::BURST_RESPONSE_STATE);
  }
};
void InitialState_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void InitialState_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status);
void InitialState_TimerCallback();
void InitialState_Exit();
#pragma endregion