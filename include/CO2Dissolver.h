#ifndef CO2_DISSOLVER__H
#define CO2_DISSOLVER__H

#include "mbed.h"
#include "OnOffMotor.h"
#include "PhaseState.h"
#include "PressureTransmitter.h"

/**
 * @brief CO2 dissolver equipment module.
 */
class CO2Dissolver
{

public:
  /** @brief Initializes the equipment module. */
  CO2Dissolver(PressureTransmitter & bpa1);

  /** @brief Starts the "Dissolve CO2" phase. */
  PhaseState dissolveCO2();

  /** @brief Holds the "Dissolve CO2" phase. */
  PhaseState hold();

  /** @brief Stops the "Dissolve CO2" phase. */
  PhaseState stop();

  /** @brief Resumes the "Dissolve CO2" phase. */
  PhaseState resume();

  /** @brief Resets the "Dissolve CO2" phase. */
  PhaseState reset();

  /** @brief Updates the "Dissolve CO2" phase. */
  PhaseState update();

  /** @brief Returns the "Dissolve CO2" phase state. */
  PhaseState getPhaseState();

private:
  /** @brief Barrel shaker electric motor. */
  OnOffMotor maa1;
  
  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter & bpa1;

  /** @brief "Dissolve CO2" phase state. */
  PhaseState state;

  /** @brief "Dissolve CO2" phase step. */
  enum class PhaseStep {STEP_1, STEP_2, STEP_3};

  /** @brief "Dissolve CO2" phase step. */
  PhaseStep step;

  /** Timer & parameters used in "Dissolve CO2" phase procedure. */
  Timer timer;
  float last_bpa1_sample; // [bar]
  constexpr static std::chrono::seconds SAMPLING_TIME = 1s;
  constexpr static float BPA1_SETTLING_THRESHOLD = 0.01 ; // [bar]

  /** @brief Handles the "Dissolve CO2" executing phase state. */
  void handleExecutingState();

  /** @brief Handles the "Dissolve CO2" stopping phase state. */
  void handleStoppingState();

  /** @brief Handles the "Dissolve CO2" holding phase state. */
  void handleHoldingState();
  
  /** @brief Handles the "Dissolve CO2" resummingstate. */
  void handleResummingState();

  /** @brief Handles the "Dissolve CO2" resetting state. */
  void handleResettingState();
  
};

#endif
