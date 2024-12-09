#include <cstring>

#include "mbed.h"
#include "WebServer.h"

/**
 *
 */
WebServer::WebServer(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe, AlarmSystem& alarm_system)
  : esp01("TeleCentro-4dc4", "silvana6523"), carbonator(carbonator), carbonation_recipe(carbonation_recipe), alarm_system(alarm_system), response_buffer("")
{

}

/**
 *
 */
void WebServer::update()
{
  
  if (esp01.hasPendingRequest()) {
    buildResponse();
    esp01.sendResponse(response_buffer);
  }
  
}

void WebServer::buildResponse()
{

  char buf[16];
  
  strcpy(response_buffer, "<!doctype html> <html> <body>");

  toString(buf, carbonation_recipe.getRecipeState());
  sprintf(response_buffer + strlen(response_buffer), "<p>Recipe state: %s</p>", buf);
  
  sprintf(response_buffer + strlen(response_buffer), "<p>Recipe step: %d</p>", carbonation_recipe.getRecipeStep());
  
  sprintf(response_buffer + strlen(response_buffer), "<p>BPA1: %.3f bar</p>", carbonator.getBPA1());
  
  std::vector<const char*> active_alarms = alarm_system.getActiveAlarms();
  
  if (not active_alarms.empty()) {
    sprintf(response_buffer + strlen(response_buffer), "<p>Alarms: %s</p>", active_alarms.back());      
  } else {
    sprintf(response_buffer + strlen(response_buffer), "<p>Alarms: None</p>");
  }
  
  strcat(response_buffer, "</body> </html>");
  
}

void WebServer::toString(char* buf, CarbonationRecipe::RecipeState state)
{

  switch (state) {

  case CarbonationRecipe::RecipeState::IDLE:
    strcpy(buf, "Idle");
    break;
    
  case CarbonationRecipe::RecipeState::RESUMMING:
    strcpy(buf, "Resumming");
    break;

  case CarbonationRecipe::RecipeState::EXECUTING:
    strcpy(buf, "Executing");
    break;
    
  case CarbonationRecipe::RecipeState::HOLDING:
    strcpy(buf, "Holding");
    break;
    
  case CarbonationRecipe::RecipeState::HELD:
    strcpy(buf, "Held");  
    break;
    
  case CarbonationRecipe::RecipeState::STOPPING:
    strcpy(buf, "Stopping");
    break;

  case CarbonationRecipe::RecipeState::STOPPED:
    strcpy(buf, "Stopped");    
    break;
    
  case CarbonationRecipe::RecipeState::COMPLETE:
    strcpy(buf, "Complete");    
    break;
    
  case CarbonationRecipe::RecipeState::RESETTING:
    strcpy(buf, "Resetting");      
    break;
  }
  
}
