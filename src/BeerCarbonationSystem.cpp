#include "BeerCarbonationSystem.h"


BeerCarbonationSystem::BeerCarbonationSystem()
  : carbonation_recipe(carbonator)
{
  
}


/** @todo Add alarm managing and synchronize process status with hmi.
 *
 */
void BeerCarbonationSystem::execute()
{

  switch (hmi.getUserCommand()) {
    
  case HMI::START_CARBONATION_RECIPE:
    carbonation_recipe.start() ;
    break ; 
    
  case HMI::STOP_CARBONATION_RECIPE:
    carbonation_recipe.stop() ;
    break ;
    
  case HMI::RESET_CARBONATION_RECIPE:
    carbonation_recipe.reset();
    break ;
    
  default:
    break ;
  }

  carbonation_recipe.execute() ;
  
}
