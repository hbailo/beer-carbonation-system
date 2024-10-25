#ifndef HMI__H
#define HMI__H

#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "ILI9341.h"
#include "PhaseState.h"
#include "mbed.h"

class HMI {

public:
  /** @brief Initializes HMI. */
  HMI(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe);

  /** @brief Updates HMI. */
  void update();

private:
  /** @brief Carbonator unit equipment. */
  Carbonator& carbonator;

  /** @brief Carbonation master recipe. */
  CarbonationRecipe& carbonation_recipe;
  
  /** @brief LCD hardware driver. */
  ILI9341 ili9341 ;

  /** @brief Prints character to screen. */
  void print(char c, uint16_t x, uint16_t y, ILI9341::Color font_color,
             ILI9341::Color background_color);

  /** @brief Prints string to screen. */
  void print(const char* str, uint16_t x, uint16_t y, ILI9341::Color font_color,
             ILI9341::Color background_color);

  /** @brief Inits home screen. */
  void initHomeScreen();

  /** @brief Updates home screen. */
  void updateHomeScreen();

  /** @brief Updates the recipe state text. */
  void updateRecipeStateText();

  /** @brief Updates the recipe step text. */
  void updateRecipeStepText();
  
  /** @brief Updates the barrel presure (QMB1) text. */
  void updateBarrelPressureText();

  /** @brief Updates the alarm indicator. */
  void updateAlarmIndicator();
  
};

#endif
