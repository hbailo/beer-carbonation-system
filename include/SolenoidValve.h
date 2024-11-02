#ifndef SOLENOID_VALVE__H
#define SOLENOID_VALVE__H

#include "mbed.h"

/**
 *  @brief Solenoid valve control module.
 *
 *  This class is designed to control a solenoid valve.
 */

class SolenoidValve
{

public:
  
  /** @brief States of the solenoid valve. */
  enum class State {OFF, ON, TURNING_OFF, TURNING_ON} ;
  
  /** @brief Constructs the control module with the specified DO pin. */
  SolenoidValve(PinName on_actutating_signal_pin, std::chrono::milliseconds response_time = 50ms) ;

  /** @brief Turns on the solenoid valve. */
  State on() ;

  /** @brief Turns off the solenoid valve. */
  State off() ;

private:

  /** @brief Digital out signal. */
  DigitalOut on_actuating_signal ;

  /** @brief Response time. */
  std::chrono::milliseconds response_time ;

  /** @brief Response time timer. */
  Timer timer ;

  /** @brief Solenoid valve state. */
  State state ;
  
} ;

#endif
