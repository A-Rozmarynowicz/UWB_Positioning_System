#include "interface.h"

void Initialize_Interface(){
    pinMode(UWB_EXCHANGE_LED, OUTPUT);
}

void UWB_Exchange_Successful() {
    digitalWrite(UWB_EXCHANGE_LED, !digitalRead(UWB_EXCHANGE_LED));
}
