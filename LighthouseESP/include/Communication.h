#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "esp_now.h"
#include "LighthouseConfig.h"

#define DATA_SIZE 20
const uint8_t BROADCAST_RECEIVER_ID = 255;
const uint8_t ACK_MESSAGE_COUNT = 5;

extern uint8_t buffer[DATA_SIZE];

enum DATA_SETUP {
  RECEIVER_ID = 0,
  TRANSMITTER_ID = 1,
  COMMAND = 2,
  SINGLE_0 = 3,
  QUAD_0 = 4,
  QUAD_1 = 8,
  QUAD_2 = 12,
  QUAD_3 = 16,
};

enum DATA_COMMANDS {
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
void Send_Ack(uint8_t receiver);
void Send_Change_To_Burst_Response(uint8_t receiver);
void Send_Burst_Query(uint8_t receiver);
void Send_Burst_Response(uint8_t receiver);
void Send_Relay_Burst_Response(uint8_t new_burster_id);
void Send_Reset_Burst_Response_Info();
void Send_End_Of_Config_Message(uint8_t receiver);
void Send_Query_Avg_Response_Time(uint8_t receiver);
void Send_Response_Avg_Response_Time(uint8_t receiver, double avg);
void Send_Master_LHG_Reset();
void Send_Query_Distance(uint8_t receiver, uint8_t target);
void Send_Response_Distance(uint8_t receiver, uint8_t target, float distance);
void Send_Set_Position(uint8_t receiver, float x, float y, float z);
}

#endif