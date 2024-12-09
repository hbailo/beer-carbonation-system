#ifndef BEER_CARBONATION_SYSTEM__H
#define BEER_CARBONATION_SYSTEM__H

#include "mbed.h"

#include "AlarmSystem.h"
#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "HMI.h"
#include "SupervisoryComputer.h"
#include "WebServer.h"

/**
 * @brief Beer carbonation system
 *
 * This class implements the process cell logic (ISA S88 design pattern), managing user interface, executing the recipes and controlling the equipment.
 *
 */
class BeerCarbonationSystem {
 
public:
  /** @brief Initializes the process cell. */
  BeerCarbonationSystem() ;    
  
  /** @brief Executes the process cell logic. */
  void update() ;

private:
  /** @brief Carbonator unit. */
  Carbonator carbonator ;
  
  /** @brief Carbonation control recipe. */
  CarbonationRecipe carbonation_recipe ;

  /** @brief Alarm system */
  AlarmSystem alarm_system;

  /** @brief Human Machine Interface. */
  HMI hmi;
  
  /** @brief Web server. */
  WebServer web_server;
  
  /** @brief Supervisory computer. */
  SupervisoryComputer supervisory_computer;
  
  /** @brief Execution timer. */
  Timer timer;
  
};

#endif
