/**
 * @file Communication.h
 * @brief Handles ESP-NOW communication and message sending.
 *
 * This file contains the main communication module for the Lighthouse project.
 * It defines:
 *  - The `MESSAGES` namespace for sending commands
 *  - The `AckStatus` struct for acknowledgment tracking
 *  - Initialization and helper functions for ESP-NOW communication
 *
 * @author Your Name
 * @date 2026-01-15
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "esp_now.h"
#include "LighthouseConfig.h"

#define DATA_SIZE 20

const uint8_t BROADCAST_RECEIVER_ID = 255;
const uint8_t ACK_MESSAGE_COUNT = 10;

enum Data_Setup {
  RECEIVER_ID = 0,
  TRANSMITTER_ID = 1,
  COMMAND = 2,
  SINGLE_0 = 3,
  QUAD_0 = 4,
  QUAD_1 = 8,
  QUAD_2 = 12,
  QUAD_3 = 16,
};

enum Data_Commands {
  MASTER_LGH_RESET,
  ACK_COM,
  UWB_START_ANCHORING,
  UWB_QUERY_COM,
  UWB_RESPONSE_COM,
  CHANGE_STATE_COM,
  QUERY_AVG_RESPONSE_TIME,
  RESPOND_AVG_RESPONSE_TIME,
  QUERY_DISTANCE,
  RESPONSE_DISTANCE,
  SET_POSITION,
  READY_FOR_OBSERVER,

  OBSERVER_QUERY_POSITION,
  OBSERVER_RESPONSE_POSITION,
  OBSERVER_QUERY_UWB_ADDRESS,
  OBSERVER_RESPONSE_UWB_ADDRESS,
  OBSERVER_ENABLE_UWB,
  OBSERVER_WAKEUP_RECKON,
};
enum Communication_Errors {
  PROTOCOL_INIT_FAIL,
  MESSAGE_SEND_FAIL,
  DELIVERY_FAIL,
  ACK_FAIL,
};

/// @brief DUPA
/// SURPA
///
/// AAAll
struct AckStatus {
  uint8_t current_ack_index;
  uint8_t target_ack_lighthouse;
};

extern AckStatus current_ack_status;
extern uint8_t transmit_buffer[DATA_SIZE]; // TODO

/**
 * @brief Initializes the communication module.
 *
 * Sets up ESP-NOW and configures callbacks.
 */
void Initialize_Communication();

/**
 * @namespace MESSAGES
 * @brief Contains all message sending functions for communication
 */
namespace MESSAGES {

/// @brief Sends an acknowledgment to a receiver.
/// @param receiver ID of the receiver
void Send_Ack(uint8_t receiver);

void Send_Change_To_UWB_Response(uint8_t receiver);
void Send_UWB_Start_Anchoring(uint8_t receiver);
void Send_UWB_Query(uint8_t receiver);
void Send_UWB_Response(uint8_t receiver);
void Send_Relay_UWB_Response(uint8_t new_uwber_id);
void Send_End_Of_Config_Message(uint8_t receiver);
void Send_Query_Avg_Response_Time(uint8_t receiver);
void Send_Response_Avg_Response_Time(uint8_t receiver, double avg);
void Send_Master_LHG_Reset();
void Send_Query_Distance(uint8_t receiver, uint8_t target);
void Send_Response_Distance(uint8_t receiver, uint8_t target, float distance);
void Send_Set_Position(uint8_t receiver);

void Send_Observer_Ready();
void Send_Observer_Position_Response();
void Send_Observer_UWB_Address_Response();
}

// Private
void _send_esp();
void _receive_callback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void _sent_callback(const uint8_t *macAddr, esp_now_send_status_t status);
void _communication_error(Communication_Errors error);


#endif