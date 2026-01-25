#include "interface.h"

/**
 * @brief Initializes interface peripherals (LED pins, etc.).
 */
void Initialize_Interface(){
    pinMode(UWB_EXCHANGE_LED, OUTPUT);
}

/**
 * @brief Blinks the UWB exchange LED once.
 */
void Blink_LED() {
    digitalWrite(UWB_EXCHANGE_LED, !digitalRead(UWB_EXCHANGE_LED));
}

/**
 * @brief Turns the error LED on to indicate a failure.
 */
void Error_LED_On(){
    digitalWrite(ERROR_LED, 1);
}