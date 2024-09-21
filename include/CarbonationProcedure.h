#ifndef CARBONATION_PROCEDURE__H
#define CARBONATION_PROCEDURE__H

#include "Carbonator.h"

class CarbonationProcedure
{

public:
  
  CarbonationProcedure(Carbonator & carbonator) ;
  void start() ;
  void execute();
  void hold() ;
  void stop() ;
  void resume() ;
  void reset() ;


private:
  
  enum Step  {STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6, STEP_7, STEP_8} ;
  enum State {IDLE, EXECUTING, HELD, STOPPED, COMPLETE} ;

  Step  step ;
  State state ;

  /** @brief Carbonator equipment module. */
  Carbonator & carbonator ;
  
} ;

#endif
