#include "mbed.h"
#include "CoordinationControl.h"


/**
 * \brief Main program.
 *
 * 
 */
int main()
{

  CoordinationControl coordination_control;
  
  while (true) {
    coordination_control.execute() ;
  }
  
}
