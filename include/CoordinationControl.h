#ifndef COORDINATION_CONTROL__H
#define COORDINATION_CONTROL__H

#include "CarbonationProcedure.h"
#include "Carbonator.h"
#include "HMIDriver.h"
#include "mbed.h"

/**
 * @brief Coordination control logic of the beer carbonation system.
 */
class CoordinationControl
{

public:

  
  /** @brief Default constructor */
  CoordinationControl() ;
  
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
