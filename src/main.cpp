#include "mbed.h"
#include "BeerCarbonationSystem.h"


/**
 * \brief Main program.
 *
 * 
 */
int main()
{

  BeerCarbonationSystem beer_carbonation_system ;
  
  while (true) {
    beer_carbonation_system.execute() ;
  }
  
}
