#include "Interface.h"

void Initialize_Interface(){
    pinMode(STATUS_BUTTON, INPUT_PULLUP);
    attachInterrupt(STATUS_BUTTON, _button_ISR, RISING);
    pinMode(DATA_TRANSFER_LED, OUTPUT);
    Data_Transfer_LED_OFF();
    pinMode(ERROR_LED, OUTPUT);
    digitalWrite(ERROR_LED, 0);
}

void Blink_LED() {
    digitalWrite(DATA_TRANSFER_LED, !digitalRead(DATA_TRANSFER_LED));
}

void Data_Transfer_LED_ON(){
    digitalWrite(DATA_TRANSFER_LED, 1);
}

void Data_Transfer_LED_OFF(){
    digitalWrite(DATA_TRANSFER_LED, 0);
}

void Error_LED_On() {
    digitalWrite(ERROR_LED, 1);
}

void ICACHE_RAM_ATTR _button_ISR() {
  State_Button_Callback(STATUS_BUTTON);
}