#ifndef ON_OFF_MOTOR__H
#define ON_OFF_MOTOR__H

#include "mbed.h"


/**
 *  @brief On off motor control module.
 *
 *  This class is designed to control an on off motor control that is activated
 *  through one on/off electric signal.
 *
 *  Command is done through the assignation of commands in the public member attributes.
 *
 *  For example, to startup the motor assign true to the on_cmd
 *  attribute and run the execute method.
 *
 *  @code{.cpp}
 *    OnOffMotor motor(DO_PIN) ;
 *
 *    motor.on_cmd = true ;
 *    motor.execute()     ; 
 *  @endcode
 *
 *  The priority of commands, from the most to the lowest, is as follow:
 *  1. Protection off command.
 *  2. Protection on command.
 *  3. Off command.
 *  4. On command.
 */
class OnOffMotor
{

public:
  
  /** @brief Protection off command signal. */
  bool protection_off_cmd ;

  /** @brief Protection on command signal. */
  bool protection_on_cmd ;

  /** @brief Off command signal. */
  bool off_cmd ;

  /** @brief On command signal. */
  bool on_cmd ;

  /** @brief States of the solenoid valve. */
  enum State {OFF, ON} ;
  
  /** @brief Constructs the control module with the specified DO pin. */
  OnOffMotor(PinName on_actutating_signal_pin) ;
  
  /** @brief Executes the control module logic. */
  void execute() noexcept ;

  /** @brief Returns the solenoid valve state. */
  State getState() const noexcept ;

private:
  
  /** @brief Solenoid valve state. */
  State state ;

  /** @brief Digital out signal. */
  DigitalOut on_actuating_signal ;
  
} ;

#endif
