#include "BeerCarbonationSystem.h"

/**
 *
 */
BeerCarbonationSystem::BeerCarbonationSystem()
  : carbonation_recipe(carbonator), alarm_system(carbonator, carbonation_recipe), hmi(carbonator, carbonation_recipe, alarm_system), supervisory_computer(carbonator, carbonation_recipe)
{
  
}


/** 
 *
 */
void BeerCarbonationSystem::update()
{

  supervisory_computer.update();
  hmi.update();
  alarm_system.update();  
  carbonation_recipe.update();
  carbonator.update();
  
}
