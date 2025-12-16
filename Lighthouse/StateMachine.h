#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include "LighthouseConfig.h"
#include "Timing.h"

namespace StateMachine {
  enum STATES {
    INITIAL_STATE = 0,
    BURST_QUERY_STATE,
    BURST_RESPONSE_STATE,
    POST_BURST_CHECK_IF_ALL_LGHS_SET_STATE,
    POST_BURST_CHECK_IF_IS_LAST_LGHS_STATE,
    RELAY_BURST_QUERING_TO_NEXT_STATE,
    INFORM_END_CONFIG_STATE,
    DISTANCE_MEASURE_RESPONSE_STATE,
    DISTANCE_MEASURE_QUERY_STATE,
    SEND_CALCULATED_POSITION_STATE,
    SAILOR_RESPONSE,
  };
};

StateMachine::STATES current_state = StateMachine::INITIAL_STATE;

void Change_State(StateMachine::STATES new_state);
void State_Enter();
void State_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void State_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status);
void State_TimerCallback();
void State_Exit();

void InitialState_Enter();
void InitialState_ReceiveCallback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void InitialState_SentCallback(const uint8_t *macAddr, esp_now_send_status_t status);
void InitialState_TimerCallback();
void InitialState_Exit();

#endif