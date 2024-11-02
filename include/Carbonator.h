#ifndef CARBONATOR__H
#define CARBONATOR__H

#include "CO2Dissolver.h"
#include "CO2Injector.h"
#include "mbed.h"
#include "OnOffMotor.h"
#include "PhaseState.h"
#include "PressureTransmitter.h"
#include "SolenoidValve.h"

/**
 *  @brief Carbonator unit.
 */
class Carbonator
{

public:
  /** @brief Initializes carbonator unit. */
  Carbonator();
  
  /** @brief Starts the "Inject CO2" phase. */
  PhaseState injectCO2(float pressure_stepoint);

  /** @brief Returns the "Inject CO2" phase state. */
  PhaseState getInjectCO2PhaseState();

  /** @brief Starts the "Dissolve CO2" phase. */
  PhaseState dissolveCO2();

  /** @brief Returns the "Dissolve CO2" phase state. */
  PhaseState getDissolveCO2PhaseState();
  
  /** @brief Holds the unit. */
  void hold();

  /** @brief Stops the unit. */
  void stop();

  /** @brief Resumes the unit. */
  void resume();

  /** @brief Resets the unit. */
  void reset();

  /** @brief Updates the recipe. */
  void update();
  
  /** @brief Returns the beer barrel pressure. */
  float getBPA1();

private:
  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter bpa1;

  /** @brief CO2 Injector. */
  CO2Injector co2_injector;

  /** @brief CO2 dissolver. */
  CO2Dissolver co2_dissolver;
  
};
  
#endif
