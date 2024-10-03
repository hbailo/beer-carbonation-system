#ifndef BEER_CARBONATION_SYSTEM__H
#define BEER_CARBONATION_SYSTEM__H

#include "CarbonationProcedure.h"
#include "Carbonator.h"
#include "HMIDriver.h"
#include "mbed.h"

/**
 * @brief Coordination control logic of the beer carbonation system.
 */
class BeerCarbonationSystem
{

public:

  
  /** @brief Default constructor */
  BeerCarbonationSystem() ;
  
  /** @brief Executes the coordination control logic. */
  void execute() ;

private:
  /** @brief Carbonator equipment module. */
  Carbonator carbonator ;
  
  /** @brief Carbonation procedure. */
  CarbonationProcedure carbonation_procedure ;
  
  /** @brief Alarm siren horn. */
  //Horn horn ;

  /** @brief HMI Driver. */
  HMIDriver hmi ;
  
} ;

#endif
