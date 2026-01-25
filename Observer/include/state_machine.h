/**
 * @file state_machine.h
 * @brief State machine interface for the observer.
 *
 * @details
 * This header defines the state machine for the observer device. It includes:
 * - Definitions of possible states
 * - Error types for state transitions
 * - Global state data and current state tracking
 * - Declarations of public state machine API functions
 * - Declarations of state-specific handlers (enter, exit, callbacks)
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "observer_config.h"

/**
 * @brief Holds data required by the state machine during runtime.
 *
 * @details
 * Contains information such as the current target lighthouse index and
 * acknowledgment index used during communication.
 */
struct State_Data {
    uint8_t target_lgh;
    uint8_t ack_index;
};

/**
 * @brief Possible states of the observer state machine.
 */
enum States {
    INITIAL = 0,
    QUERY_POSITIONS = 1,
    QUERY_DISTANCES = 2,
};

/**
 * @brief Errors that can occur within the state machine.
 */
enum State_Machine_Errors {
  INEXISTING_STATE,
  WRONG_TRANSITION,
};

/**
 * @brief Maximum number of ACK retries.
 */
const uint8_t MAX_ACK_NUMBER = 5;

/**
 * @brief Maximum number of ACK retries.
 */
extern States current_state;

/**
 * @brief Global state data used by the state machine.
 */
extern State_Data current_state_data;

void Reset_And_Initialize_Machine();
void State_Machine_Error(State_Machine_Errors error);

void Change_State(States new_state);
void State_Enter();
void State_ReceiveCallback(const uint8_t* data, int dataLen);
void State_SentCallback();
void State_TimerCallback(Timer_Callbacks timer_callback);
void State_SailorCommand(Sailor_Commands command);
void State_UWB_New_Range(uint16_t device, float range, float rx_power);
void State_Exit();

void Initial_Enter();
void Initial_ReceiveCallback(const uint8_t* data, int dataLen);
void Initial_SentCallback();
void Initial_TimerCallback(Timer_Callbacks timer_callback);
void Initial_SailorCommand(Sailor_Commands command);
void Initial_UWB_New_Range(uint16_t device, float range, float rx_power);
void Initial_Exit();

void Query_Positions_Enter();
void Query_Positions_ReceiveCallback(const uint8_t* data, int dataLen);
void Query_Positions_SentCallback();
void Query_Positions_TimerCallback(Timer_Callbacks timer_callback);
void Query_Positions_SailorCommand(Sailor_Commands command);
void Query_Positions_UWB_New_Range(uint16_t device, float range, float rx_power);
void Query_Positions_Exit();

void Query_Distances_Enter();
void Query_Distances_ReceiveCallback(const uint8_t* data, int dataLen);
void Query_Distances_SentCallback();
void Query_Distances_TimerCallback(Timer_Callbacks timer_callback);
void Query_Distances_SailorCommand(Sailor_Commands command);
void Query_Distances_UWB_New_Range(uint16_t device, float range, float rx_power);
void Query_Distances_Exit();

#endif