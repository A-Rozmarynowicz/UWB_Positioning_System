#include "HardwareSerial.h"
#include "esp32-hal-timer.h"
#include "timing.h"

hw_timer_t* ack_timer = NULL;
bool ack_timer_triggered = false;

/**
 * @brief Initializes the ACK timer.
 *
 * @details
 * Creates and configures the hardware timer used to trigger ACK timeouts.
 * The timer is set up with a prescaler of 8000 (source clock 80 MHz),
 * configured as an auto-reloading timer, and attaches the interrupt handler.
 * If timer initialization fails, the error handler is executed.
 */
void Initialize_Timers(){
  ack_timer = timerBegin(0, 8000, true); // Źródło zegarów to 80MHz
  if (ack_timer == nullptr){
    Timing_Error();
  }
  Stop_Ack_Timer();
  timerAttachInterrupt(ack_timer, &_on_ack_timer_timeout, true);
  timerAlarmWrite(ack_timer, ACK_TIMER_PERIOD_MS*10, true);
  timerAlarmEnable(ack_timer);
};

/**
 * @brief Starts the ACK timer.
 *
 * @details
 * Enables the timer counting, so that the ACK timeout ISR will be triggered
 * after the configured period.
 */
void Start_Ack_Timer(){
  timerStart(ack_timer);
}

/**
 * @brief Stops the ACK timer.
 *
 * @details
 * Disables the timer counting to prevent further ACK timeout callbacks.
 */
void Stop_Ack_Timer(){
  timerStop(ack_timer);
  }

/**
 * @brief Handles timing-related errors.
 *
 * @details
 * Called when timer initialization or operation fails.
 * Triggers an error LED.
 */
void Timing_Error(){
  Error_LED_On();
}

/**
 * @brief Interrupt Service Routine for the ACK timer.
 *
 * @details
 * Called when the ACK timer reaches its timeout. Stops the timer and
 * notifies the state machine about the ACK timeout.
 */
void IRAM_ATTR _on_ack_timer_timeout(){
    Stop_Ack_Timer();
    State_TimerCallback(Timer_Callbacks::ACK);
  };