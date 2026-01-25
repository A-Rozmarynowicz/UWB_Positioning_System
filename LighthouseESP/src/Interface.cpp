#include "Interface.h"

/**
 * @brief Initialize GPIOs for LEDs and the status button.
 *
 * Configures the status button as an interrupt source and initializes
 * LED GPIOs to their default states.
 *
 * @return void
 */
void Initialize_Interface(){
    pinMode(STATUS_BUTTON, INPUT_PULLUP);
    attachInterrupt(STATUS_BUTTON, _button_ISR, RISING);
    pinMode(DATA_TRANSFER_LED, OUTPUT);
    Data_Transfer_LED_OFF();
    pinMode(ERROR_LED, OUTPUT);
    digitalWrite(ERROR_LED, 0);
}

/**
 * @brief Toggle the state of the data transfer LED.
 *
 * @return void
 */
void Blink_LED() {
    digitalWrite(DATA_TRANSFER_LED, !digitalRead(DATA_TRANSFER_LED));
}

/**
 * @brief Turn on the data transfer LED.
 *
 * @return void
 */
void Data_Transfer_LED_ON(){
    digitalWrite(DATA_TRANSFER_LED, 1);
}


/**
 * @brief Turn off the data transfer LED.
 *
 * @return void
 */
void Data_Transfer_LED_OFF(){
    digitalWrite(DATA_TRANSFER_LED, 0);
}

/**
 * @brief Turn on the error indicator LED.
 *
 * @return void
 */
void Error_LED_On() {
    digitalWrite(ERROR_LED, 1);
}

/**
 * @brief Interrupt Service Routine for the status button.
 *
 * This ISR is executed on a rising edge of the status button signal
 * and forwards the event to the state machine handler.
 *
 * @return void
 */
void ICACHE_RAM_ATTR _button_ISR() {
  State_Button_Callback(STATUS_BUTTON);
}