#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "esp_now.h"
#include "observer_config.h"

#define DATA_SIZE 20
const uint8_t BROADCAST_RECEIVER_ID = 255;
const uint8_t ACK_MESSAGE_COUNT = 5;

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
  BURST_QUERY_COM,
  BURST_RESPONSE_COM,
  CHANGE_STATE_COM,
  RESET_BURST_INFO,
  QUERY_AVG_RESPONSE_TIME,
  RESPOND_AVG_RESPONSE_TIME,
  QUERY_DISTANCE,
  RESPONSE_DISTANCE,
  SET_POSITION,
  READY_FOR_SAILOR,

  OBSERVER_QUERY_POSITION,
  OBSERVER_RESPONSE_POSITION,
  OBSERVER_ENABLE_UWB,
};

enum COMMUNICATION_ERRORS {
  PROTOCOL_INIT_FAIL,
  MESSAGE_SEND_FAIL,
  DELIVERY_FAIL,
  ACK_FAIL,
};

struct AckStatus {
  uint8_t current_ack_index;
  uint8_t target_ack_lighthouse;
};

extern AckStatus current_ack_status;
extern uint8_t transmit_buffer[DATA_SIZE];

void Initialize_Communication();

void Send_ESP();

void Receive_Callback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void Sent_Callback(const uint8_t *macAddr, esp_now_send_status_t status);
void Communication_Error(COMMUNICATION_ERRORS error);

namespace MESSAGES {
    void Send_Query_Position(uint8_t lgh_index);
}

#endif