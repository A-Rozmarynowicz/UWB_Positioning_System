#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "LighthouseConfig.h" // TODO tutaj Timers.h
#include "Timing.h"

hw_timer_t* uwb_activation_timer = NULL;
hw_timer_t* ack_timer = NULL;

/**
 * @brief Initializes hardware timers for UWB activation and ACK timeout.
 *
 * This function sets up two ESP32 hardware timers, attaches interrupt callbacks,
 * configures the alarm periods, and enables the timers.
 */
void Initialize_Timers(){
    uwb_activation_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz
    if (uwb_activation_timer == nullptr){
      Timing_Error();
    }
    Stop_UWB_Activation_Timer();
    timerAttachInterrupt(uwb_activation_timer, &_on_UWB_activation_timer_timeout, true);
    timerAlarmWrite(uwb_activation_timer, UWB_ACTIVATION_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(uwb_activation_timer);

    ack_timer = timerBegin(1, 8000, true); // Źródło zegarów to 80MHz
    if (ack_timer == nullptr){
      Timing_Error();
    }
    Stop_Ack_Timer();
    timerAttachInterrupt(ack_timer, &_on_ack_timer_timeout, true);
    timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
    timerAlarmEnable(ack_timer);
  };

/**
 * @brief Interrupt handler for UWB activation timer.
 *
 * Stops the timer and triggers the state machine callback for UWB activation.
 */
void IRAM_ATTR _on_UWB_activation_timer_timeout(){
  Stop_UWB_Activation_Timer();
  State_TimerCallback(Timer_Callbacks::UWB_ACTIVATION);
};

/**
 * @brief Interrupt handler for ACK timeout timer.
 *
 * Stops the timer and triggers the state machine callback for ACK timeout.
 */
void IRAM_ATTR _on_ack_timer_timeout(){
  Stop_Ack_Timer();
  State_TimerCallback(Timer_Callbacks::ACK);
};

/**
 * @brief Starts the UWB activation timer.
 */
void Start_UWB_Activation_Timer(){
  timerStart(uwb_activation_timer);
};


/**
 * @brief Stops the UWB activation timer.
 */
void Stop_UWB_Activation_Timer(){
  timerStop(uwb_activation_timer);
};

/**
 * @brief Handles timing related errors.
 *
 * This function prints an error message and turns on the error LED.
 */
void Timing_Error() {
  Error_LED_On();
}

/**
 * @brief Starts the ACK timeout timer.
 */
void Start_Ack_Timer(){
  timerStart(ack_timer);
}

/**
 * @brief Stops the ACK timeout timer.
 */
void Stop_Ack_Timer(){
  timerStop(ack_timer);
}