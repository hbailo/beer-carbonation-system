#include "SolenoidValve.h"


/**
 *  @param on_actuating_signal_pin the actuating signal DO pin.
 *  @param response_time the solenoid valve response time.
 */
SolenoidValve::SolenoidValve(PinName on_actuating_signal_pin, std::chrono::milliseconds response_time = 50ms)
  : on_actuating_signal(on_actuating_signal_pin, false), response_time(response_time), state(OFF)
{
  
}


SolenoidValve::State SolenoidValve::on()
{

  switch (state) {
    
  case OFF: 
    on_actuating_signal = true ;
    timer.start() ;    
    state = TURNING_ON ;
    break ;

  case ON:
    break ;
    
  case TURNING_OFF:
    on_actuating_signal = true ;
    timer.reset() ;
    state = TURNING_ON ;
    break ;
    
  case TURNING_ON:
    
    if (duration_cast<milliseconds>(timer.elapsed_time()).count() > response_time) {
      timer.stop() ;
      state = ON ;
    }
    
    break ;
    
  }

  return state ;
  
}


SolenoidValve::State SolenoidValve::off()
{

  switch (state) {

  case OFF:
    break ;
    
  case ON:
    on_actuating_signal = false ;
    timer.start() ;
    state = TURNING_OFF ;
    break ;
    
  case TURNING_OFF:

    if (duration_cast<milliseconds>(timer.elapsed_time()).count() > response_time) {
      timer.stop() ;
      state = OFF ;
    }
    
    break ;
    
  case TURNING_ON:
    on_actuating_signal = false ;
    timer.reset() ;
    state = TURNING_OFF ;
    break ;
    
  }

  return state ;
  
}
