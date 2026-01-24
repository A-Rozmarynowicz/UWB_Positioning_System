#include "interface.h"

void Initialize_Interface(){
    pinMode(UWB_EXCHANGE_LED, OUTPUT);
}

void Blink_LED() {
    digitalWrite(UWB_EXCHANGE_LED, !digitalRead(UWB_EXCHANGE_LED));
}

void Error_LED_On(){
    digitalWrite(ERROR_LED, 1);
}