#ifndef ON_OFF_MOTOR__H
#define ON_OFF_MOTOR__H

#include "mbed.h"

/**
 *  @brief On off motor control module.
 *
 *  This class is designed to control an on off motor control that is activated
 *  through one on/off electric signal.
 *
 */
class OnOffMotor
{

public:  
  /** @brief States of the motor. */
  enum class State {OFF, ON, TURNING_OFF, TURNING_ON};
  
  /** @brief Constructs the control module with the specified DO pin. */
  OnOffMotor(PinName on_actutating_signal_pin, std::chrono::seconds response_time = 5s);

  /** @brief Turns on the motor */
  State on();

  /** @brief Turns off the motor. */
  State off();

private:

  /** @brief Digital out signal. */
  DigitalOut on_actuating_signal;

  /** @brief Response time. */
  std::chrono::seconds response_time;

  /** @brief Response time timer. */
  Timer timer;

  /** @brief Motor state. */
  State state;
  
};

#endif
