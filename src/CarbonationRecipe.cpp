#include "CarbonationRecipe.h"
#include "Carbonator.h"


/**
 *  The recipe is initialized in IDLE state ready to start.
 *  @param carbonator the assigned carbonator unit.
 */
CarbonationRecipe::CarbonationRecipe(Carbonator& carbonator)
  : carbonator(carbonator), recipe_state(RecipeState::IDLE), step(STEP_1)
{
  
}

/**
 *  Signals the recipe to transition to the EXECUTING state if it is in IDLE
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
 *  Signals the recipe to transition to the HELD state if it is in EXECUTING
 *  state, otherwise it does nothing.
 *  The recipe pass through the HOLDING intermediate state before reaching the HELD state.
 *
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::hold()
{

  if (recipe_state == RecipeState::EXECUTING) {
    recipe_state = RecipeState::HOLDING ;
  }

  return recipe_state;
  
}

/**
 *  Signals the recipe to transition to the STOPPED state if it is in EXECUTING or HELD
 *  state, otherwise it does nothing.
 *  The recipe pass through the STOPPING intermediate state before reaching the STOPPED state.
 *
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::stop()
{

  if (recipe_state == RecipeState::EXECUTING || recipe_state == RecipeState::HELD) {
    recipe_state = RecipeState::STOPPING;
  }

  return recipe_state;
  
}

/**
 *  Signals the recipe to transition to the EXECUTING state if it is in HELD
 *  state, otherwise it does nothing.
 *
 *  The recipe pass through the RESUMMING intermediate state before reaching the EXECUTING state.
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::resume()
{

  if (recipe_state == RecipeState::HELD) {
    carbonator.resume();
    recipe_state = RecipeState::EXECUTING;
  }

  return recipe_state;
  
}

/**
 *  Signals the recipe to transition to the IDLE state if it is in COMPLETE or
 *  STOPPED state, otherwise it does nothing.
 *  The recipe pass through the RESETTING intermediate state before reaching the IDLE state. 
 *  @todo It forwards the signal to the carbonator unit.
 * 
 *  @return the recipe state.
 */ 
CarbonationRecipe::RecipeState CarbonationRecipe::reset()
{

  if (recipe_state == RecipeState::COMPLETE || recipe_state == RecipeState::STOPPED) {
    carbonator.reset();         // TODO: check logic
    step = Step::STEP_1;
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
 *  This method executes the recipe procedure.
 *  The recipe procedure is implemented as a state machine where
 *  each state is a step in the procedure.
 */
void CarbonationRecipe::handleExecutingState()
{

  switch (step) {

  case Step::STEP_1:
    
    if (carbonator.injectCO2(3)) {
      step = Step::STEP_2 ;
    }
      
    break ;

  case Step::STEP_2:
    
    if (carbonator.dissolveCO2()) {

      if (carbonator.getBPA1() < 0.9) {
        step = Step::STEP_3 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
	
    break ;

  case Step::STEP_3:
    
    if (carbonator.injectCO2(2)) {
      step = Step::STEP_4 ;
    }
      
    break ;

  case Step::STEP_4:
    
    if (carbonator.dissolveCO2()) {
      
      if (carbonator.getBPA1() < 0.9) {
        step = STEP_5 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
    
    break ;
      
  case Step::STEP_5:
    
    if (carbonator.injectCO2(1)) {
      step = STEP_6 ;
    }
    
    break ;
      
  case STEP_6:
    
    if (carbonator.dissolveCO2()) {

      if (carbonator.getBPA1() < 0.9) {
        step = STEP_5 ;
      } else if (carbonator.getBPA1() > 1) {
        stop() ; 
      } else {
        recipe_state = RecipeState::COMPLETE ;
      }
    }
    
    break ;

  }
  
}
