#include "SolenoidValve.h"


/**
 *  @param on_actuating_signal_pin the actuating signal DO pin.
 */
SolenoidValve::SolenoidValve(PinName on_actuating_signal_pin)
  : on_actuating_signal(on_actuating_signal_pin)
{
  
}


/**
 *  This method clears the commands assigning false to each at the end of the call.
 */
void SolenoidValve::execute() noexcept
{

  // Control commands processing & ON actuating signal computing
  if (protection_off_cmd) {
    on_actuating_signal = false ;
    state = OFF ;
    
  } else if (protection_on_cmd) {
    on_actuating_signal = true ;
    state = ON ;
    
  } else if (off_cmd) {
    on_actuating_signal = false ;
    state = OFF;
    
  } else if (on_cmd) {
    on_actuating_signal = true ;
    state = ON ;
  }

  protection_off_cmd = protection_on_cmd = off_cmd = on_cmd = false ;
  
}


/**
 *  @return the solenoid valve state.
 */
SolenoidValve::State SolenoidValve::getState() const noexcept
{

  return state ;
  
}
