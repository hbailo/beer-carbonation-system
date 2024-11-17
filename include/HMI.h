#ifndef HMI__H
#define HMI__H

#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "ILI9341.h"
#include "PhaseState.h"
#include "XPT2046.h"
#include "mbed.h"

/**
 * @brief Human-Machine Interface (HMI) for the carbonation system.
 * 
 * The HMI class manages the display and touch interactions on the screen,
 * allowing users to monitor and interact with the carbonation process.
 * It includes functionalities for displaying text, updating the home screen,
 * and handling touch events.
 */
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

  /** @brief Touch screen driver. */
  XPT2046 xpt2046 ;

  /** @brief Touch screen states. */
  enum class TouchState{IDLE, PRESSED, RELEASED};

  /** @brief Touch screen state. */
  TouchState touch_state;

  /** @brief Coordinates of the last detected touch point. */
  struct {
    uint16_t x, y; // [px]
  } touch_point;
  
  /** @brief Prints a single character to the screen at a specified location. */
  void print(char c, uint16_t x, uint16_t y, ILI9341::Color font_color,
             ILI9341::Color background_color);

  /** @brief Prints a string to the screen at a specified location. */
  void print(const char* str, uint16_t x, uint16_t y, ILI9341::Color font_color,
             ILI9341::Color background_color);

  /** @brief Updates the touch point location. */
  void updateTouchPoint();

  /** @brief Handles on touch pressed event. */
  void handleOnTouchPressed();

  /** @brief Handles on touch released event. */
  void handleOnTouchReleased();
  
  /** @brief Inits the content of the home screen. */
  void initHomeScreen();

  /** @brief Updates the content of the home screen. */
  void updateHomeScreen();

  /** @brief Updates the recipe state text. */
  void updateRecipeStateText();

  /** @brief Updates the recipe step text. */
  void updateRecipeStepText();
  
  /** @brief Updates the barrel presure (QMB1) text. */
  void updateBarrelPressureText();

  /** @brief Updates the alarm indicator. */
  void updateAlarmIndicator();

  /** @brief Updates the touch input status for the home screen. */
  void updateHomeScreenTouch();
  
};

#endif
