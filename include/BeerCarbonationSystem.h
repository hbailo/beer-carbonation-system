#ifndef BEER_CARBONATION_SYSTEM__H
#define BEER_CARBONATION_SYSTEM__H

#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "HMI.h"
#include "mbed.h"

/**
 * @brief Beer carbonation system
 *
 * This class implements the process cell logic (ISA S88 design pattern), managing user interface, executing the recipes and controlling the equipment.
 */
class BeerCarbonationSystem
{

public:
  
  /** @brief Initializes the process cell. */
  BeerCarbonationSystem() ;    
  
  /** @brief Executes the process cell logic. */
  void execute() ;

private:
  
  /** @brief Carbonator unit. */
  Carbonator carbonator ;
  
  /** @brief Carbonation control recipe. */
  CarbonationRecipe carbonation_recipe ;
 
  /** @brief Human Machine Interface. */
  HMI hmi ;

  /** @brief Alarm siren. */
  // Siren siren ;
  
} ;

#endif
