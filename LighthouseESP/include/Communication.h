/**
 * @file Communication.h
 * @brief ESP-NOW based communication interface for Lighthouse devices.
 *
 * @details
 * This file defines the communication protocol, data layout, commands,
 * and message handling functions used for wireless communication between
 * Lighthouse units and observers using ESP-NOW.
 *
 * It includes:
 * - Fixed-size data buffers and protocol constants
 * - Enumerations describing message layout and command types
 * - Error codes related to communication failures
 * - Structures used to track ACK message state
 * - High-level message sending API
 * - Internal (private) callbacks and helper functions
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "esp_now.h"
#include "LighthouseConfig.h"


/**
 * @brief Size of the ESP-NOW transmit buffer in bytes.
 */
#define DATA_SIZE 20

/**
 * @brief Receiver ID used for broadcast messages.
 */
const uint8_t BROADCAST_RECEIVER_ID = 255;

/**
 * @brief Number of ACK messages expected during acknowledgment procedures.
 */
const uint8_t ACK_MESSAGE_COUNT = 150;

/**
 * @enum Data_Setup
 * @brief Byte offsets and layout definitions for the communication data frame.
 *
 * This enumeration defines positions of specific fields inside the
 * transmit/receive buffer used by the communication protocol.
 */
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

/**
 * @enum Data_Commands
 * @brief List of all supported communication commands.
 *
 * Defines the command identifiers exchanged between Lighthouse devices,
 * masters, and observers.
 */
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

/**
 * @enum Communication_Errors
 * @brief Communication-related error codes.
 */
enum Communication_Errors {
  PROTOCOL_INIT_FAIL,
  MESSAGE_SEND_FAIL,
  DELIVERY_FAIL,
  ACK_FAIL,
};

/**
 * @struct Ack_Status
 * @brief Structure used to track acknowledgment state.
 */
struct Ack_Status {
  uint8_t current_ack_index;
  uint8_t target_ack_lighthouse;
};

extern Ack_Status current_ack_status;
extern uint8_t transmit_buffer[DATA_SIZE];

void Initialize_Communication();

/**
 * @namespace MESSAGES
 * @brief High-level message construction and transmission API.
 *
 * This namespace groups functions responsible for creating and sending
 * protocol-compliant messages between devices.
 */
namespace MESSAGES {
void Send_Ack(uint8_t receiver);
void Send_Change_To_UWB_Response(uint8_t receiver);
void Send_UWB_Start_Anchoring(uint8_t receiver);
void Send_UWB_Query(uint8_t receiver);
void Send_UWB_Response(uint8_t receiver);
void Send_Relay_UWB_Response(uint8_t new_uwber_id);
void Send_End_Of_Config_Message(uint8_t receiver);
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