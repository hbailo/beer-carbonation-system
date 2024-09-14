#include <cstdint>
#include "mbed.h"


/**
 *  \brief Solenoid valve control module.
 *
 * 
 */
class SolenoidValveCtrlMod
{

public:
  
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

  /** \brief Executes the control module logic. */
  void execute() ;

  /** */
  bool isOn() noexcept ;

  /** */
  bool isOff() noexcept ;
private:
  
  /** Operation mode. */
  Mode mode ;

  /** Solenoid valve state. */
  State state ;

  DigitalOut on_actuating_signal ;
  
} ;
