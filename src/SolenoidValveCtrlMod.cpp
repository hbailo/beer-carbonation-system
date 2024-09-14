#include "SolenoidValveCtrlMod.h"


bool SolenoidValveCtrlMod::execute(bool manual_on_cmd, bool manual_off_cmd) noexcept
{

  // On actuating signal computing
  if (protection_off_cmd) {
    on_actuating_signal = OFF ;
    
  } else if (protection_on_cmd) {
    on_actuating_signal = ON ;
    
  } else if (enabling_off_cmd) {

    if ((manual_off_cmd and mode == MANUAL) or (auto_off_cmd and mode == AUTO)) {
      on_actuating_signal = OFF ;
    }

  } else if (enabling_on_cmd) {
      
    if ((manual_on_cmd and mode == MANUAL) or (auto_on_cmd and mode == AUTO)) {
      on_actuating_signal = ON ;
    }
      
  }
  
  // Mode commands processing
  if (manual_mode_cmd) {
    mode = MANUAL ;
  } else if (auto_mode_cmd) {
    mode = AUTO ;
  }
  
}


bool SolenoidValveCtrlMod::isOn() noexcept
{

  return state == ON ;
  
}


bool SolenoidValveCtrlMod::isOff() noexcept
{

  return state == OFF ;
  
}

