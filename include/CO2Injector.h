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
  
  /** @brief Starts the "Inject CO2" phase. */
  PhaseState injectCO2(float pressure);
  
  /** @brief Holds the "Inject CO2" phase. */
  PhaseState hold();

  /** @brief Stops the "Inject CO2" phase. */
  PhaseState stop();

  /** @brief Resumes the "Inject CO2" phase. */
  PhaseState resume();

  /** @brief Resets the "Inject CO2" phase. */
  PhaseState reset();

  /** @brief Updates the "Inject CO2" phase. */
  PhaseState update();

  /** @brief Returns the "Inject CO2" phase state. */
  PhaseState getPhaseState();
  
private:
  /** @brief CO2 shut off valve. */
  SolenoidValve qmb1;

  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter &bpa1;
  
  /** @brief "Inject CO2" phase state. */
  PhaseState state;

  /** @brief Steps of the "Inject CO2" phase. */
  enum class PhaseStep {STEP_1, STEP_2, STEP_3};

  /** @brief "Inject CO2" phase step. */
  PhaseStep step;

  /** @brief "Inject CO2" phase pressure setpoint. */
  float pressure_setpoint;
  
  /** @brief Handles the "Inject CO2" executing phase state. */
  void handleExecutingState();

  /** @brief Handles the "Inject CO2" stopping phase state. */
  void handleStoppingState();

  /** @brief Handles the "Inject CO2" holding phase state. */
  void handleHoldingState();
  
  /** @brief Handles the "Inject CO2" resummingstate. */
  void handleResummingState();

  /** @brief Handles the "Inject CO2" resetting state. */
  void handleResettingState();

} ;

#endif
