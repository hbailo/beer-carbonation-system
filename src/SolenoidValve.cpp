#include "SolenoidValve.h"


/**
 *  @param on_actuating_signal_pin the actuating signal DO pin.
 *  @param response_time the solenoid valve response time.
 */
SolenoidValve::SolenoidValve(PinName on_actuating_signal_pin, std::chrono::milliseconds response_time)
  : on_actuating_signal(on_actuating_signal_pin, false), response_time(response_time), state(State::OFF)
{
  
}


SolenoidValve::State SolenoidValve::on()
{

  switch (state) {
    
  case State::OFF: 
    on_actuating_signal = true ;
    timer.start() ;    
    state = State::TURNING_ON ;
    break ;

  case State::ON:
    break ;
    
  case State::TURNING_OFF:
    on_actuating_signal = true ;
    timer.reset() ;
    state = State::TURNING_ON ;
    break ;
    
  case State::TURNING_ON:
    
    if (duration_cast<milliseconds>(timer.elapsed_time()).count() > response_time) {
      timer.stop() ;
      state = State::ON ;
    }
    
    break ;
    
  }

  return state ;
  
}


SolenoidValve::State SolenoidValve::off()
{

  switch (state) {

  case State::OFF:
    break ;
    
  case State::ON:
    on_actuating_signal = false ;
    timer.start() ;
    state = State::TURNING_OFF ;
    break ;
    
  case State::TURNING_OFF:

    if (duration_cast<milliseconds>(timer.elapsed_time()).count() > response_time) {
      timer.stop() ;
      state = State::OFF ;
    }
    
    break ;
    
  case State::TURNING_ON:
    on_actuating_signal = false ;
    timer.reset() ;
    state = State::TURNING_OFF ;
    break ;
    
  }

  return state ;
  
}
