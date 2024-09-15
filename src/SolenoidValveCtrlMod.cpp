#include "SolenoidValveCtrlMod.h"


/** Initializes the control module with the passed digital output pin. */
SolenoidValveCtrlMod::SolenoidValveCtrlMod(PinName on_actuating_signal_pin)
    : on_actuating_signal(on_actuating_signal_pin)
{
  
}


void SolenoidValveCtrlMod::execute(const SolenoidValveCtrlMod::Commands & cmds) noexcept
{

  // Mode commands processing
  if (cmds.manual_mode_cmd) {
    mode = MANUAL ;
  } else if (cmds.auto_mode_cmd) {
    mode = AUTO ;
  }
  
  // Control commands processing & ON actuating signal computing
  if (cmds.protection_off_cmd) {
    on_actuating_signal = OFF ;
    state = OFF ;
    
  } else if (cmds.protection_on_cmd) {
    on_actuating_signal = ON ;
    state = ON ;
    
  } else if (cmds.enabling_off_cmd) {

    if ((cmds.manual_off_cmd and mode == MANUAL) or (cmds.auto_off_cmd and mode == AUTO)) {
      on_actuating_signal = OFF ;
      state = OFF ;
    }

  } else if (cmds.enabling_on_cmd) {
      
    if ((cmds.manual_on_cmd and mode == MANUAL) or (cmds.auto_on_cmd and mode == AUTO)) {
      on_actuating_signal = ON ;
      state = ON ;
    }

  }
  
}


bool SolenoidValveCtrlMod::isOn() const noexcept
{

  return state == ON ;
  
}


bool SolenoidValveCtrlMod::isOff() const noexcept
{

  return state == OFF ;
  
}

