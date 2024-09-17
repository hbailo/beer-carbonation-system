#include "CarbonationProcedure.h"


CarbonationProcedure::CarbonationProcedure(Carbonator & carbonator)
    : carbonator(carbonator)
{
  
}

void CarbonationProcedure::start()
{

  if (state == IDLE) {
    state = EXECUTING ; 
  }
  
}


void CarbonationProcedure::execute()
{

  if (state != EXECUTING) {
    return ;
  }
  
  switch (step) {

  case STEP_1:
    
    if (carbonator.injectCO2(3)) {
      step = STEP_2 ;
    }
      
    break ;

  case STEP_2:
    
    if (carbonator.dissolveCO2()) {

      if (carbonator.getBPA1() < 0.9) {
	step = STEP_3 ;
      } else {
	state = COMPLETE ;
      }
    }
	
    break ;

  case STEP_3:
    
    if (carbonator.injectCO2(2)) {
      step = STEP_4 ;
    }
      
    break ;

  case STEP_4:
    
    if (carbonator.dissolveCO2()) {

      if (carbonator.getBPA1() < 0.9) {
	step = STEP_5 ;
      } else {
	state = COMPLETE ;
      }
    }
    
    break ;
      
  case STEP_5:
    
    if (carbonator.injectCO2(1)) {
      step = STEP_6 ;
    }
    
    break ;
      
  case STEP_6:
    
    if (carbonator.dissolveCO2()) {

      if (carbonator.getBPA1() < 0.9) {
	step = STEP_5 ;
      } else {
	state = COMPLETE ;
      }
    }
    
    break ;
      
  default:
    stop() ;
      
  }
  
}


void CarbonationProcedure::hold()
{

  if (state == EXECUTING) {
    state = HELD ;
  }
  
}


void CarbonationProcedure::stop()
{

  if (state == EXECUTING) {
    carbonator.stop() ;    
    state = STOPPED;
  }
  
}


void CarbonationProcedure::reset()
{

  if (state == COMPLETE || state == STOPPED) {
    step  = STEP_1 ;
    state = IDLE ;
  }
  
}


void CarbonationProcedure::resume()
{
  
  if (state == HELD) {
    state = EXECUTING ;
  }
  
}
