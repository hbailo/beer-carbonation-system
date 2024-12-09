#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "AlarmSystem.h"
#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "ESP01.h"
#include "mbed.h"

/**
 *
 */
class WebServer {

public:
  /** @brief Initializes the web server. */
  WebServer(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe, AlarmSystem& alarm_system);

  /** @brief Updates the web server. */
  void update();
  
private:
  /** @brief ESP01 hardware driver. */
  ESP01 esp01;
  
  Carbonator& carbonator;
  CarbonationRecipe& carbonation_recipe;
  AlarmSystem& alarm_system;

  void buildResponse();
  char response_buffer[256];

  void toString(char* buf, CarbonationRecipe::RecipeState state);
  
};
  
#endif
