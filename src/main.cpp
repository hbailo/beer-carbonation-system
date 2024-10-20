#include "BeerCarbonationSystem.h"

/**
 * @brief Main program sweep (cycle)
 */
int main()
{

  BeerCarbonationSystem beer_carbonation_system ;
  
  while (true) {
    beer_carbonation_system.update() ;
  }
  
}
