#ifndef SOLENOID_VALVE_CONTROL_MODULE__H
#define SOLENOID_VALVE_CONTROL_MODULE__H

#include <cstdint>
#include "mbed.h"


/**
 *  \brief Solenoid valve control module.
 * 
 */
class SolenoidValveCtrlMod
{

public:
  
  /** \brief Control module commands. */
  struct Commands {
    bool protection_off_cmd ;
    bool enabling_off_cmd ;
    bool manual_off_cmd ;
    bool auto_off_cmd ;
    bool manual_mode_cmd ;
    bool auto_mode_cmd ;
    bool auto_on_cmd ;
    bool manual_on_cmd ;
    bool enabling_on_cmd ;
    bool protection_on_cmd ;
  } ;

  /** \brief Constructor. */
  SolenoidValveCtrlMod(PinName on_actutating_signal_pin) ;
  
  /** \brief Executes the control module logic.*/
  void execute(const Commands & commands) noexcept ;
  
  /** */
  bool isOn() const noexcept ;

  /** */
  bool isOff() const noexcept ;
  
private:
    
  /** \brief Modes of operation. */
  enum Mode : int_least8_t {
    AUTO,
    MANUAL
  } ;

  /** \brief States of the solenoid valve. */
  enum State : int_least8_t {
    OFF,
    ON
  } ;

  /** Operation mode. */
  Mode mode ;

  /** Solenoid valve state. */
  State state ;

  DigitalOut on_actuating_signal ;
  
} ;

#endif
