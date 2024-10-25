#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "PhaseState.h"

/**
 *  The recipe is initialized in IDLE state ready to start.
 *  @param carbonator the assigned carbonator unit.
 */
CarbonationRecipe::CarbonationRecipe(Carbonator& carbonator)
  : carbonator(carbonator), recipe_state(RecipeState::IDLE), step(RecipeStep::STEP_1)
{
  
}

/**
 *  Commands the recipe to transition to the EXECUTING state if it is in IDLE
 *  state, otherwise it does nothing.
 * 
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::start()
{

  if (recipe_state == RecipeState::IDLE) {
    recipe_state = RecipeState::EXECUTING;
  }

  return recipe_state;
  
}

/**
 *  Commands the recipe to transition to the HELD state if it is in EXECUTING
 *  state, otherwise it does nothing.
 *  The recipe pass through the HOLDING transitional state before reaching the HELD state.
 *
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::hold()
{

  if (recipe_state == RecipeState::EXECUTING) {
    carbonator.hold();
    recipe_state = RecipeState::HOLDING;
  }

  return recipe_state;
  
}

/**
 *  Commands the recipe to transition to the STOPPED state if it is in EXECUTING or HELD
 *  state, otherwise it does nothing.
 *  The recipe pass through the STOPPING transitional state before reaching the STOPPED state.
 *
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::stop()
{

  if (recipe_state == RecipeState::EXECUTING || recipe_state == RecipeState::HELD ||
      recipe_state == RecipeState::HOLDING   || recipe_state == RecipeState::RESUMMING) {
    carbonator.stop();
    recipe_state = RecipeState::STOPPING; 
  }

  return recipe_state;
  
}

/**
 *  Commands the recipe to transition to the EXECUTING state if it is in HELD
 *  state, otherwise it does nothing.
 *  The recipe pass through the RESUMMING transitional state before reaching the EXECUTING state.
 *  
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::resume()
{

  if (recipe_state == RecipeState::HELD) {
    carbonator.resume();    
    recipe_state = RecipeState::RESUMMING;
  }

  return recipe_state;
  
}

/**
 *  Commands the recipe to transition to the IDLE state if it is in COMPLETE or
 *  STOPPED state, otherwise it does nothing.
 *  The recipe pass through the RESETTING transitional state before reaching the IDLE state. 
 * 
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::reset()
{

  if (recipe_state == RecipeState::COMPLETE or recipe_state == RecipeState::STOPPED) {
    carbonator.reset();
    step = RecipeStep::STEP_1;
    recipe_state = RecipeState::RESETTING;
  }

  return recipe_state;
  
}

/**
 *  @return the recipe state.
 */
CarbonationRecipe::RecipeState CarbonationRecipe::update()
{

  switch (recipe_state) {

  case RecipeState::EXECUTING:
    handleExecutingState();
    break;

  case RecipeState::STOPPING:
    handleStoppingState();
    break;

  case RecipeState::HOLDING:
    handleHoldingState();
    break;

  case RecipeState::RESUMMING:
    handleResummingState();
    break;

  case RecipeState::RESETTING:
    handleResettingState();
    break;
    
  case RecipeState::IDLE:
  case RecipeState::HELD:
  case RecipeState::STOPPED:
  case RecipeState::COMPLETE:
    break;
    
  }

  return recipe_state;
  
}

/**
 *  @return the recipe state.
 */
CarbonationRecipe::RecipeState CarbonationRecipe::getRecipeState()
{

  return recipe_state;
  
}


/**
 *  @return the recipe step number.
 */
int CarbonationRecipe::getRecipeStep()
{

  return static_cast<int>(step) + 1;
  
}

/**
 *  This method executes the recipe procedure.
 *  The recipe procedure is implemented as a state machine where
 *  each state is a step in the procedure.
 */
void CarbonationRecipe::handleExecutingState()
{

  switch (step) {

  case RecipeStep::STEP_1:
    
    if (carbonator.injectCO2(3) == PhaseState::COMPLETE) {
      step = RecipeStep::STEP_2 ;
    }
      
    break ;

  case RecipeStep::STEP_2:
    
    if (carbonator.dissolveCO2() == PhaseState::COMPLETE) {

      if (carbonator.getBPA1() < 0.9) {
        step = RecipeStep::STEP_3 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
	
    break ;

  case RecipeStep::STEP_3:
    
    if (carbonator.injectCO2(2) == PhaseState::COMPLETE) {
      step = RecipeStep::STEP_4 ;
    }
      
    break ;

  case RecipeStep::STEP_4:
    
    if (carbonator.dissolveCO2() == PhaseState::COMPLETE) {
      
      if (carbonator.getBPA1() < 0.9) {
        step = RecipeStep::STEP_5 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
    
    break ;
      
  case RecipeStep::STEP_5:
    
    if (carbonator.injectCO2(1) == PhaseState::COMPLETE) {
      step = RecipeStep::STEP_6 ;
    }
    
    break ;
      
  case RecipeStep::STEP_6:
    
    if (carbonator.dissolveCO2() == PhaseState::COMPLETE) {

      if (carbonator.getBPA1() < 0.9) {
        step = RecipeStep::STEP_5 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
    
    break ;

  }

}

/**
 *
 */
void CarbonationRecipe::handleStoppingState()
{

  PhaseState inject_co2_phase_state = carbonator.getInjectCO2PhaseState();

  PhaseState dissolve_co2_phase_state = carbonator.getDissolveCO2PhaseState();

  if ((inject_co2_phase_state == PhaseState::COMPLETE or
       inject_co2_phase_state == PhaseState::STOPPED or
       inject_co2_phase_state == PhaseState::IDLE) and
      (dissolve_co2_phase_state == PhaseState::COMPLETE or
       dissolve_co2_phase_state == PhaseState::STOPPED or
       dissolve_co2_phase_state == PhaseState::IDLE)) {
    recipe_state = RecipeState::STOPPED;
  }

}

/**
 *
 */
void CarbonationRecipe::handleHoldingState()
{

  PhaseState inject_co2_phase_state = carbonator.getInjectCO2PhaseState();

  PhaseState dissolve_co2_phase_state = carbonator.getDissolveCO2PhaseState();

  if ((inject_co2_phase_state == PhaseState::COMPLETE or
       inject_co2_phase_state == PhaseState::STOPPED or
       inject_co2_phase_state == PhaseState::IDLE or
       inject_co2_phase_state == PhaseState::HELD) and
      (dissolve_co2_phase_state == PhaseState::COMPLETE or
       dissolve_co2_phase_state == PhaseState::STOPPED or
       dissolve_co2_phase_state == PhaseState::IDLE or
       dissolve_co2_phase_state == PhaseState::HELD)) {
    recipe_state = RecipeState::HELD;
  }
  
}

/**
 *
 */
void CarbonationRecipe::handleResummingState()
{

  PhaseState inject_co2_phase_state = carbonator.getInjectCO2PhaseState();

  PhaseState dissolve_co2_phase_state = carbonator.getDissolveCO2PhaseState();
  
  if ((inject_co2_phase_state == PhaseState::COMPLETE or
       inject_co2_phase_state == PhaseState::STOPPED or
       inject_co2_phase_state == PhaseState::IDLE or
       inject_co2_phase_state == PhaseState::EXECUTING) and
      (dissolve_co2_phase_state == PhaseState::COMPLETE or
       dissolve_co2_phase_state == PhaseState::STOPPED or
       dissolve_co2_phase_state == PhaseState::IDLE or
       dissolve_co2_phase_state == PhaseState::EXECUTING)) {
    recipe_state = RecipeState::EXECUTING;
  }
    
}

/**
 *  Sets the IDLE recipe state once the carbonator unit phases are in IDLE
 *  state.
 */
void CarbonationRecipe::handleResettingState()
{

  if (carbonator.getInjectCO2PhaseState() == PhaseState::IDLE and
      carbonator.getDissolveCO2PhaseState() == PhaseState::IDLE) {
    recipe_state = RecipeState::IDLE;
  }
  
}
