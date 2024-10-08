#ifndef CARBONATION_RECIPE__H
#define CARBONATION_RECIPE__H

#include "Carbonator.h"

/**
 * @brief Carbonation master recipe
 *
 * This class is an ISA S88 master recipe that defines one procedure to
 * carbonatize a beer barrel.
*/
class CarbonationRecipe
{

public:
  
  /** @brief Initializes the recipe by assigning the carbonator unit. */
  CarbonationRecipe(Carbonator & carbonator) ;

  /** @brief Starts the recipe procedure. */
  void start() ;

  /** @brief Holds the recipe procedure. */
  void hold() ;

  /** @brief Stops the recipe procedure. */
  void stop() ;

  /** @brief Resumes the recipe procedure. */
  void resume() ;

  /** @brief Resets the recipe procedure. */
  void reset() ;

  /** @brief Executes the recipe procedure. */
  void execute() ;

private:
  
  enum State {IDLE, EXECUTING, HELD, STOPPED, COMPLETE};
  State state ;

  enum Step {STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6} ;
  Step step ;

  /** @brief Carbonator equipment module. */
  Carbonator & carbonator ;

  /** @todo Add batch specific information, id, parameters reports, status      
   * indication, etc for HMI interface.
   */
  
} ;

#endif
