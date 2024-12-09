#include "BeerCarbonationSystem.h"

/**
 *
 */
BeerCarbonationSystem::BeerCarbonationSystem()
    : carbonator(),
      carbonation_recipe(carbonator),
      alarm_system(carbonator, carbonation_recipe),
      hmi(carbonator, carbonation_recipe, alarm_system),
      web_server(carbonator, carbonation_recipe, alarm_system),
      supervisory_computer(carbonator, carbonation_recipe)
{

  timer.start();
  
}

/** 
 *
 */
void BeerCarbonationSystem::update()
{

  supervisory_computer.update();
  web_server.update();
  hmi.update();
  alarm_system.update();  
  carbonation_recipe.update();
  carbonator.update();
   
}
