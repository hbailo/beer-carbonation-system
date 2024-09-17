#ifndef SOLENOID_VALVE__H
#define SOLENOID_VALVE__H

#include "mbed.h"


/**
 *  @brief Solenoid valve control module.
 *
 *  This class is designed to control a solenoid valve through the assignation
 *  of commands in the public member attributes.
 *
 *  For example, to activate the solenoid valve assign true to the on_cmd
 *  attribute and run the execute method.
 *
 *  @code{.cpp}
 *    SolenoidValve valve(DO_PIN) ;
 *
 *    valve.on_cmd = true ;
 *    valve.execute()     ; 
 *  @endcode
 *
 *  The priority of commands, from the most to the lowest, is as follow:
 *  1. Protection off command.
 *  2. Protection on command.
 *  3. Off command.
 *  4. On command.
 */
class SolenoidValve
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
  SolenoidValve(PinName on_actutating_signal_pin) ;
  
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
