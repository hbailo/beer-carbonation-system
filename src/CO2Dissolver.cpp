#include "CO2Dissolver.h"
#include <cmath>

using namespace std;

CO2Dissolver::CO2Dissolver(PressureTransmitter & bpa1)
  : maa1(D3), bpa1(bpa1), state(PhaseState::IDLE), step(PhaseStep::STEP_1), timer(), last_bpa1_sample(0.0)
{
  
}

/**
 *  This method keeps the agitator on until the CO2 dissolves completely.
 *  Complete dissolution is determined when the current sample and the sample
 *  from one second ago differ by less than 10 mbar.
 *
 *  @return the current phase state.
 *
 *  @todo Fix pressure threshold and sampling period hardcoding.
 */
PhaseState CO2Dissolver::dissolveCO2()
{

  if (state == PhaseState::IDLE) {
    state = PhaseState::EXECUTING;
  }
    

  if (state == PhaseState::EXECUTING) {

    switch (step) {

    case PhaseStep::STEP_1: // Start MAA1

      if (maa1.on() == OnOffMotor::State::ON) {
        last_bpa1_sample = bpa1;
        timer.start();
        step = PhaseStep::STEP_2;
      }

      break;

    case PhaseStep::STEP_2: // Wait until BPA1 is settled

      if (timer.elapsed_time() > SAMPLING_TIME) {
        float current_bpa1_sample = bpa1;

        if (abs(current_bpa1_sample - last_bpa1_sample) < BPA1_SETTLING_THRESHOLD) {
          timer.stop() ;
          step = PhaseStep::STEP_3;
        } else {
          last_bpa1_sample = current_bpa1_sample;
          timer.reset();
        }
        
      }

      break ;

    case PhaseStep::STEP_3: // Stop MAA1

      if (maa1.off() == OnOffMotor::State::OFF) {
        state = PhaseState::COMPLETE;
      }

      break;
      
    }
    
  }
  
  return state;
  
}


PhaseState CO2Dissolver::stop()
{

  switch (state) {

  case PhaseState::EXECUTING:
  case PhaseState::RESUMMING:
  case PhaseState::HOLDING:
  case PhaseState::HELD:
    state = PhaseState::STOPPING;
    break;
    
  case PhaseState::STOPPING:

    if (maa1.off() == OnOffMotor::State::OFF) {
      timer.stop();
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


PhaseState CO2Dissolver::reset()
{

  switch (state) {

  case PhaseState::STOPPED:
  case PhaseState::COMPLETE:
    timer.reset();
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

PhaseState CO2Dissolver::hold()
{

  switch (state) {

  case PhaseState::EXECUTING:
    state = PhaseState::HOLDING;
    break;

  case PhaseState::HOLDING:

    if (maa1.off() == OnOffMotor::State::OFF) {
      timer.stop() ;
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

PhaseState CO2Dissolver::resume()
{

  switch (state) {
    
  case PhaseState::HELD:
    state = PhaseState::RESUMMING;
    break;

  case PhaseState::RESUMMING:
    timer.reset();
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
