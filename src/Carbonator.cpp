#include "Carbonator.h"
#include "mbed.h"
#include "PhaseState.h"


Carbonator::Carbonator()
  : bpa1(PC_0), co2_injector(bpa1), co2_dissolver(bpa1)
{
  
}

/**
 *  This method is the unit phase interface to the "Inject CO2" equipment phase.
 *  Before forwarding the command it checks the interlock logic of the unit.
 *  
 *  @param[in] pressure the desired pressure in bar.
 *
 *  @return the "Inject CO2" phase state.
 */
PhaseState Carbonator::injectCO2(float pressure_setpoint)
{

  // TODO: Add unit interlock logic.

  return co2_injector.injectCO2(pressure_setpoint);
  
}

/**
 *  @return the "Inject CO2" phase state.
 */
PhaseState Carbonator::getInjectCO2PhaseState()
{

  // TODO: Add unit interlock logic.

  return co2_injector.getPhaseState();
  
}

/**
 *  This method is the unit phase interface to the "Dissolve CO2" equipment phase.
 *  Before forwarding the command it checks the interlock logic of the unit.
 *
 *  @return the "Dissolve CO2" phase state.
 */
PhaseState Carbonator::dissolveCO2()
{

  // TODO: Add unit interlock logic.

  return co2_dissolver.dissolveCO2();
  
}

/**
 *  @return the "Dissolve CO2" phase state.
 */
PhaseState Carbonator::getDissolveCO2PhaseState()
{

  // TODO: Add unit interlock logic.

  return co2_dissolver.getPhaseState();
  
}

/**
 *  Forwards the stop command to the equipment phases.
 *  @return STOPPED if all equipment phases are stopped, STOPPING otherwise. 
 */
void Carbonator::stop()
{

  co2_dissolver.stop();
  co2_injector.stop();
  
}

/**
 *  Forwards the hold command to the equipment phases.
 *  @return HELD if all equipment phases are stopped, HOLDING otherwise.
 */
void Carbonator::hold()
{

  co2_dissolver.hold();
  co2_injector.hold();

}

/**
 *  Forwards the resume command to the equipment phases.
 *  @return EXECUTING if all equipment phases are resumed, RESUMMING otherwise.
 */
void Carbonator::resume()
{

  co2_dissolver.resume();
  co2_injector.resume();
  
}

/**
 *
 */
void Carbonator::reset()
{

  co2_dissolver.reset();
  co2_injector.reset();

}

/**
 *
 */
void Carbonator::update()
{

  co2_dissolver.update();
  co2_injector.update();

}

/**
 *  @return beer barrel pressure in bar.
 */
float Carbonator::getBPA1()
{

  return bpa1;
  
}
