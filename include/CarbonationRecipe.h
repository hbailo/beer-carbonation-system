#ifndef CARBONATION_RECIPE__H
#define CARBONATION_RECIPE__H

#include "Carbonator.h"

/**
 *  @brief Carbonation master recipe
 *
 *  This class is an ISA S88 master recipe that defines one procedure to
 *  carbonatize a beer barrel.
 */
class CarbonationRecipe
{

public:
  /** @brief States of the recipe. */
  enum class RecipeState {IDLE, RESUMMING, EXECUTING, HOLDING, HELD, STOPPING, STOPPED, COMPLETE, RESETTING};
  
  /** @brief Initializes the recipe by assigning a carbonator unit. */
  CarbonationRecipe(Carbonator& carbonator);

  /** @brief Starts the recipe. */
  RecipeState start();

  /** @brief Holds the recipe. */
  RecipeState hold();

  /** @brief Stops the recipe. */
  RecipeState stop();

  /** @brief Resumes the recipe. */
  RecipeState resume();

  /** @brief Resets the recipe. */
  RecipeState reset();
  
  /** @brief Updates the recipe. */
  RecipeState update();

private:
  /** @brief Assigned carbonator unit. */
  Carbonator& carbonator;
  
  /** @brief Recipe state. */
  RecipeState recipe_state;

  /** @brief Steps of the recipe. */
  enum class Step {STEP_1, STEP_2, STEP_3, STEP_4, STEP_5, STEP_6};

  /** @brief Recipe step. */
  Step step;
  
  /** @brief Handles the executing recipe state. */
  void handleExecutingState();

  /** @brief Handles the stopping recipe state. */
  void handleStoppingState();

  /** @brief Handles the holding recipe state. */
  void handleHoldingState();
  
  /** @brief Handles the resumming recipe state. */
  void handleResummingState();

  /** @brief Handles the resetting recipe state. */
  void handleResettingState();
  
  /** @todo
   *  FEATURE: Add batch specific information, id, parameters reports, status
   *  indication, etc for logging.
   */
};

#endif
