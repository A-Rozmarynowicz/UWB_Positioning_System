#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "esp_now.h"
#include "LighthouseConfig.h"
#include "StateMachine.h"

#define DATA_SIZE 20
const uint8_t BROADCAST_RECEIVER_ID = 255;

enum DATA_SETUP {
  DS_RECEIVER_ID = 0,
  DS_TRANSMITTER_ID = 1,
  DS_MODE = 2,
  DS_MESSAGE = 3,
  DS_EXECUTION_TIME = 4,
  DS_X_POS = 8,
  DS_Y_POS = 12,
  DS_Z_POS = 16,
};

enum COMMUNICATION_ERRORS {
  PROTOCOL_INIT_FAIL,
  MESSAGE_SEND_FAIL,
  DELIVERY_FAIL,
};

void Initialize_Communication();

void Send_ESP(const uint8_t* buffer);

void Receive_Callback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void Sent_Callback(const uint8_t *macAddr, esp_now_send_status_t status);

void Communication_Error(COMMUNICATION_ERRORS error);

#endif