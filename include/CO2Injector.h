#ifndef CO2_INJECTOR__H
#define CO2_INJECTOR__H

#include "mbed.h"
#include "PhaseState.h"
#include "PressureTransmitter.h"
#include "SolenoidValve.h"

/**
 * @brief CO2 injector equipment module.
 */
class CO2Injector
{

public:
  /** @brief Initializes the equipment module. */
  CO2Injector(PressureTransmitter& bpa1);
  
  /** @brief Injects CO2 up to pressure. */
  PhaseState injectCO2(float pressure);
  
  /** @brief Holds the equipment phase. */
  PhaseState hold();

  /** @brief Stops the equipment phase. */
  PhaseState stop();

  /** @brief Resumes the equipment phase. */
  PhaseState resume();

  /** @brief Resets the equipment phase. */
  PhaseState reset();

private:
  /** @brief CO2 shut off valve. */
  SolenoidValve qmb1;

  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter &bpa1;
  
  /** @brief Inject CO2 phase state. */
  PhaseState state;

  /** @brief Steps of the Inject CO2 phase. */
  enum class PhaseStep {STEP_1, STEP_2, STEP_3};

  /** @brief Inject CO2 phase step. */
  PhaseStep step;
  
} ;

#endif
