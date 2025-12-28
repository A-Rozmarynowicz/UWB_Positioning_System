#include "Interface.h"

void Initialize_Interface(){
    pinMode(DATA_TRANSFER_LED, OUTPUT);
    Data_Transfer_LED_OFF();
}

void Data_Transfer_LED_ON(){
    digitalWrite(DATA_TRANSFER_LED, 1);
}

void Data_Transfer_LED_OFF(){
    digitalWrite(DATA_TRANSFER_LED, 0);
}