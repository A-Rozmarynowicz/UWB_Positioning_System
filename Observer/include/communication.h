/**
 * @file communication.h
 * @brief ESP-NOW communication interface and message definitions.
 *
 * @details
 * This header defines the communication protocol used by the system,
 * including message formats, command identifiers, error codes, and helper
 * functions for sending and receiving ESP-NOW packets.
 *
 * It provides:
 * - Data layout and command enums for ESP-NOW messages
 * - Global buffers and state structures for acknowledgements
 * - Initialization and message sending utilities
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "esp_now.h"
#include "observer_config.h"

#define DATA_SIZE 20
const uint8_t BROADCAST_RECEIVER_ID = 255;
const uint8_t ACK_MESSAGE_COUNT = 5;

/**
 * @brief Indices inside the ESP-NOW data packet.
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
 * @brief Commands used in ESP-NOW communication.
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
 * @brief Possible communication errors.
 */
enum Communication_Errors {
  PROTOCOL_INIT_FAIL,
  MESSAGE_SEND_FAIL,
  DELIVERY_FAIL,
  ACK_FAIL,
};

/**
 * @brief Acknowledgement status used for tracking message retries.
 */
struct AckStatus {
  uint8_t current_ack_index;
  uint8_t target_ack_lighthouse;
};

/**
 * @brief Current acknowledgement status
 */
extern AckStatus current_ack_status;

/**
 * @brief Current data prepared to send.
 */
extern uint8_t transmit_buffer[DATA_SIZE];

// Public
void Initialize_Communication();

namespace MESSAGES {
    void Send_Query_Position(uint8_t lgh_index);
    void Send_Wakeup_Reckon();
}

// Private
void _send_esp();
void _receive_callback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void _sent_callback(const uint8_t *macAddr, esp_now_send_status_t status);
void _communication_error(Communication_Errors error);

#endif