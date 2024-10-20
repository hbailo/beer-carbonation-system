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

  /** @brief Injects CO2 up to pressure. */
  PhaseState dissolveCO2();
  
  /** @brief Holds the equipment phase. */
  PhaseState hold();

  /** @brief Stops the equipment phase. */
  PhaseState stop();

  /** @brief Resumes the equipment phase. */
  PhaseState resume();

  /** @brief Resets the equipment phase. */
  PhaseState reset();

private:
  /** @brief Barrel shaker electric motor. */
  OnOffMotor maa1;
  
  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter & bpa1;

  /** @brief Dissolve CO2 phase state. */
  PhaseState state;

  /** @brief Dissolve CO2 phase step. */
  enum class PhaseStep {STEP_1, STEP_2, STEP_3};
  PhaseStep step;

  /** Members & parameters used in phase procedure. */
  Timer timer;
  float last_bpa1_sample; // [bar]
  constexpr static std::chrono::seconds SAMPLING_TIME = 1s;
  constexpr static float BPA1_SETTLING_THRESHOLD = 0.1 ; // [bar]
  
};

#endif
