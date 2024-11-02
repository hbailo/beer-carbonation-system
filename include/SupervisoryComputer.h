#ifndef SUPERVISORY_COMPUTER__H
#define SUPERVISORY_COMPUTER__H

#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "mbed.h"

/**
 *  @brief Supervisory computer
 *
 *  This class implements a supervisory computer interface to the system.
 *  Communication with the computer is through UART interface at 9600 baud.
 */
class SupervisoryComputer {

public:
  /** @brief Initializes the supervisory computer */
  SupervisoryComputer(Carbonator& Carbonator, CarbonationRecipe& carbonation_recipe);

  /** @brief Updates the supervisory computer. */
  void update();

private:
  /** @brief Carbonator unit equipment. */
  Carbonator& carbonator;

  /** @brief Carbonation master recipe. */
  CarbonationRecipe& carbonation_recipe;
  
  /** @brief UART endpoint. */
  UnbufferedSerial uart;

  /** @brief Reporting states. */
  enum class ReportingState {IDLE, REPORTING};

  /** @brief Reporting state. */
  ReportingState reporting_state;

  constexpr static const char* USAGE_INFO = "Usage: Send key to issue a command.\n\rCommands:\n\r1: Start the recipe.\n\r2: Stop the recipe.\n\r3: Hold the recipe.\n\r4: Resume the recipe.\n\r5: Reset the recipe.\n\rr: Start process information reporting.\n\rR: Stop process information reporting.\n\rA: Acknowledge alarm.\n\rh: Show this help.\n\r";
  
};

#endif
