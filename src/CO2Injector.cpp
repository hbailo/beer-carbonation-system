#include "CO2Injector.h"
#include "PhaseState.h"
#include "mbed.h"

/**
 * @param bpa1 the shared BPA1 pressure transmitter.
 */
CO2Injector::CO2Injector(PressureTransmitter& bpa1)
  : qmb1(LED1), bpa1(bpa1), state(PhaseState::IDLE), step(PhaseStep::STEP_1)
{
  
}

/**
 *  This method starts the "Inject CO2" phase procedure if BPA ≤ pressure setpoint parameter.
 *  
 *  @param[in] pressure_setpoint_parameter the desired barrel pressure in bar.
 *
 *  @return the current phase state.
 */
PhaseState CO2Injector::injectCO2(float pressure_setpoint_parameter)
{
  
  switch (state) {

  case PhaseState::IDLE:

    if (bpa1 <= pressure_setpoint_parameter) {
      pressure_setpoint = pressure_setpoint_parameter;
      state = PhaseState::EXECUTING;      
    }

    break;
    
  case PhaseState::EXECUTING:
  case PhaseState::RESUMMING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
  case PhaseState::STOPPING:
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::RESETTING:    
    break;
  }

  return state;
  
}

/**
 *  @return the current phase state.
 */
PhaseState CO2Injector::hold()
{

  switch (state) {

  case PhaseState::EXECUTING:
    state = PhaseState::HOLDING;
    break;
    
  case PhaseState::RESUMMING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
  case PhaseState::STOPPING:
  case PhaseState::IDLE:
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::RESETTING:    
    break;
  }

  return state;
}

/**
 *  @return the current phase state.
 */
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
  case PhaseState::IDLE:
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::RESETTING:    
    break;
  }

  return state;
  
}


PhaseState CO2Injector::reset()
{

  switch (state) {

  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
    state = PhaseState::RESETTING;
    break;

  case PhaseState::IDLE:
  case PhaseState::RESUMMING:
  case PhaseState::EXECUTING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
  case PhaseState::STOPPING:
  case PhaseState::RESETTING:    
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
  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
  case PhaseState::IDLE:
  case PhaseState::EXECUTING:
  case PhaseState::HOLDING:
  case PhaseState::STOPPING:
  case PhaseState::RESETTING:    
    break;
    
  }

  return state;

}

/**
 *
 */
PhaseState CO2Injector::update()
{

  switch (state) {

  case PhaseState::EXECUTING:
    handleExecutingState();
    break;

  case PhaseState::STOPPING:
    handleStoppingState();
    break;
    
  case PhaseState::HOLDING:
    handleHoldingState();
    break;

  case PhaseState::RESUMMING:
    handleResummingState();
    break;

  case PhaseState::RESETTING:
    handleResettingState();
    break;

  case PhaseState::COMPLETE:
    reset();
    break;
    
  case PhaseState::STOPPED:
  case PhaseState::IDLE:    
  case PhaseState::HELD:
    break;
    
  }

  return state;
  
}

/**
 *  @return the current phase state.
 */
PhaseState CO2Injector::getPhaseState()
{

  return state;
  
}

/**
 *  "Inject CO2" phase procedure:
 *  Keeps the solenoid valve QMB1 open until BPA1 reaches the pressure setpoint. Then closes QMB1.
 */
void CO2Injector::handleExecutingState()
{

  switch (step) {

  case PhaseStep::STEP_1: // Open QMB1
    
    if (qmb1.on() == SolenoidValve::State::ON) {
      step = PhaseStep::STEP_2;
    }

    break;

  case PhaseStep::STEP_2: // Wait until BPA1 reaches the specified pressure

    if (bpa1 > pressure_setpoint) {
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

/**
 *
 */
void CO2Injector::handleStoppingState()
{
  
  if (qmb1.off() == SolenoidValve::State::OFF) {
    state = PhaseState::STOPPED;
  }

}

/**
 *
 */
void CO2Injector::handleHoldingState()
{

  if (qmb1.off() == SolenoidValve::State::OFF) {
    state = PhaseState::HELD;
  }
  
}

/**
 *
 */
void CO2Injector::handleResummingState()
{

  step  = PhaseStep::STEP_1;    
  state = PhaseState::EXECUTING;

}

/**
 *
 */
void CO2Injector::handleResettingState()
{

  step  = PhaseStep::STEP_1;    
  state = PhaseState::IDLE;
  
}
