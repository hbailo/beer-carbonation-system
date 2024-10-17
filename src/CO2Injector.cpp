#include "CO2Injector.h"

/**
 * @param bpa1 the shared BPA1 pressure transmitter.
 */
CO2Injector::CO2Injector(PressureTransmitter& bpa1)
  : qmb1(D2), bpa1(bpa1), state(PhaseState::IDLE), step(PhaseStep::STEP_1)
{
  
}

/**
 *  @param[in] pressure the desired pressure in bar.
 *
 *  This method keeps the solenoid valve QMB1 open until the specified
 *  pressure is reached in BPA1. Then closes QMB1.
 *
 *  @return the current phase state.
 */
PhaseState CO2Injector::injectCO2(float pressure)
{

  if (state == PhaseState::IDLE) {

    if (bpa1 > pressure) {
      state = PhaseState::COMPLETE;
    } else {
      state = PhaseState::EXECUTING;
    }
    
  }

  if (state == PhaseState::EXECUTING) {

    switch (step) {

    case PhaseStep::STEP_1: // Open QMB1
    
      if (qmb1.on() == SolenoidValve::State::ON) {
        step = PhaseStep::STEP_2;
      }

      break;

    case PhaseStep::STEP_2: // Wait until BPA1 reaches the specified pressure

      if (bpa1 > pressure) {
        step = PhaseStep::STEP_3;
      }

      break ;

    case PhaseStep::STEP_3: // Close QMB1

      if (qmb1.off() == SolenoidValve::State::OFF) {
        state = PhaseState::COMPLETE;
      }

      break;
      
    }
    
  }
  
  return state;
  
}


PhaseState CO2Injector::stop()
{

  switch (state) {

  case PhaseState::EXECUTING:
  case PhaseState::RESUMMING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
    state = PhaseState::STOPPING;
    break;
    
  case PhaseState::STOPPING:

    if (qmb1.off() == SolenoidValve::State::OFF) {
      state = PhaseState::STOPPED;
    }

    break;

  case PhaseState::IDLE:
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
    break;
    
  }

  return state;
  
}


PhaseState CO2Injector::reset()
{

  switch (state) {

  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
    step  = PhaseStep::STEP_1;
    state = PhaseState::IDLE;
    break;

  case PhaseState::IDLE:
  case PhaseState::RESUMMING:
  case PhaseState::EXECUTING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
  case PhaseState::STOPPING:
    break;
    
  }

  return state;
  
}

PhaseState CO2Injector::hold()
{

  switch (state) {

  case PhaseState::EXECUTING:
    state = PhaseState::HOLDING;
    break;

  case PhaseState::HOLDING:

    if (qmb1.off() == SolenoidValve::State::OFF) {
      state = PhaseState::HELD;
    }

    break;

  case PhaseState::RESUMMING:
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::IDLE:    
  case PhaseState::HELD:
  case PhaseState::STOPPING:
    break;
    
  }

  return state;
  
}

PhaseState CO2Injector::resume()
{

  switch (state) {
    
  case PhaseState::HELD:
    state = PhaseState::RESUMMING;
    break;

  case PhaseState::RESUMMING:
    step  = PhaseStep::STEP_1;    
    state = PhaseState::EXECUTING;
    break;
    
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::IDLE:
  case PhaseState::EXECUTING:
  case PhaseState::HOLDING:
  case PhaseState::STOPPING:
    break;
    
  }

  return state;
  
}
