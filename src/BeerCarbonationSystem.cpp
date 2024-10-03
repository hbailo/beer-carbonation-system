#include "BeerCarbonationSystem.h"
#include "CarbonationProcedure.h"


BeerCarbonationSystem::BeerCarbonationSystem()
  : carbonation_procedure(carbonator)
{
  
}


/** @todo Add alarm managing and synchronize process status with hmi.
 *
 */
void BeerCarbonationSystem::execute()
{

  switch (hmi.getUserCommand()) {
    
  case HMIDriver::START_CARBONATION_PROCEDURE:
    carbonation_procedure.start() ;
    break ; 
    
  case HMIDriver::STOP_CARBONATION_PROCEDURE:
    carbonation_procedure.stop() ;
    break ;
    
  case HMIDriver::RESET_CARBONATION_PROCEDURE:
    carbonation_procedure.reset();
    break ;
    
  default:
    break ;
  }

  carbonation_procedure.execute() ;
  
}
