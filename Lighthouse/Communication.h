#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "LighthouseConfig.h"
#include "StateMachine.h"

#define DATA_SIZE 20
const uint8_t BROADCAST_RECEIVER_ID = 255;

void Send_ESP(const uint8_t* buffer);

void Receive_Callback(const uint8_t* macAddr, const uint8_t* data, int dataLen);
void Sent_Callback(const uint8_t *macAddr, esp_now_send_status_t status);

#endif