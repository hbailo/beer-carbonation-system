#include "AlarmSystem.h"
#include "CarbonationRecipe.h"
#include "PinNames.h"
#include "font.h"
#include "HMI.h"
#include "ILI9341.h"
#include "mbed.h"
#include <cmath>
#include <cstdint>
#include <system_error>
#include <vector>

/**
 * Initializes the HMI system with references to the carbonation equipment 
 * and the carbonation recipe, setting up the display and touch input drivers.
 * 
 * @param carbonator Reference to the Carbonator unit.
 * @param carbonation_recipe Reference to the CarbonationRecipe being used.
 */
HMI::HMI(Carbonator &carbonator, CarbonationRecipe &carbonation_recipe, AlarmSystem& alarm_system)
    : carbonator(carbonator),
      carbonation_recipe(carbonation_recipe),
      alarm_system(alarm_system),
      ili9341(PB_5, PB_4, PB_3, PA_4 /*PB_12*/, PC_7, PA_15),
      xpt2046(PB_15, PC_2, PB_13, PB_12, PC_6,
          [this]() { handleOnTouchPressed(); },
          [this]() { handleOnTouchReleased(); }),
      touch_state(TouchState::IDLE)
      
{

  initHomeScreen();
  
}


/**
 * This function should be called periodically to refresh the display 
 * and handle any user interactions. It updates the touch input state,
 * checks for display updates, and ensures that the interface remains responsive.
 */
void HMI::update()
{

  updateHomeScreen();
  
}

/**
 *  Displays a character at the specified x and y coordinates with the 
 *  chosen background color.
 * 
 *  @param c Character to display.
 *  @param x X coordinate position in pixels.
 *  @param y Y coordinate position in pixels.
 *  @param font_color Color of the font.
 *  @param background_color Color of the background.
 * 
 *  @todo Fix font size hardcoding.
 */
void HMI::print(char c, uint16_t x, uint16_t y, ILI9341::Color text_color, ILI9341::Color background_color)
{
  
  ILI9341::Color frame_memory_area_data[8 * 16];

  const uint8_t* c_frame = printable_ascii_8x16_font[c - 32]; // NOTE: First printable ASCII character (whitespace) has index 32.
  int pixel = 0;
  
  for (uint8_t row = 0; row < 16; ++row) {
    uint8_t c_frame_row = c_frame[row];

    for (uint8_t col = 0; col < 8; ++col) {

      if (c_frame_row & 0x01) {
        frame_memory_area_data[pixel] = text_color;
      } else {
        frame_memory_area_data[pixel] = background_color;
      }
      
      c_frame_row >>= 1;
      pixel += 1;
    }

  }

  ili9341.drawImage(x, y, 8, 16, frame_memory_area_data);
  
}

/**
 *  Displays a string starting at the specified x and y coordinates
 *  with the chosen background color.
 * 
 *  @param str String to display.
 *  @param x X coordinate position in pixels.
 *  @param y Y coordinate position in pixels.
 *  @param font_color Color of the font.
 *  @param background_color Color of the background.
 * 
 *  @todo Fix font size hardcoding.
 */
void HMI::print(const char* str, uint16_t x, uint16_t y, ILI9341::Color text_color, ILI9341::Color background_color)
{
  
  while (*str) {
    print(*str, x, y, text_color, background_color);
    
    x += 8;
    ++str;
  }

}

/**
 *  Touch point coordinates are scaled to screen pixels.
 *  @note Fix scaling hardcoding.
 */
void HMI::updateTouchPoint()
{

  uint16_t x, y;
  
  xpt2046.getTouchPoint(x, y);

  float mx = -0.085606;
  float bx = 336.784730;

  touch_point.x = lround(x * mx + bx);
  
  float my = 0.065977;
  float by = -13.853627;

  touch_point.y = lround(y * my + by);
  
}

void HMI::handleOnTouchPressed()
{

  switch (touch_state) {
    
  case TouchState::IDLE:
    touch_state = TouchState::PRESSED;
    break;

  case TouchState::PRESSED:
  case TouchState::RELEASED:
    break;
    
  }
  
}

void HMI::handleOnTouchReleased()
{

  switch (touch_state) {
    
  case TouchState::PRESSED:
    touch_state = TouchState::RELEASED;
    break;

  case TouchState::IDLE:
  case TouchState::RELEASED:
    break;
    
  }
    
}

/**
 *  @todo Fix buttons hardcoding
 */
void HMI::initHomeScreen()
{

  ili9341.fillScreen(ILI9341::Color::BLACK);

  // Process cell status
  print("Recipe state: ", 0, 0, ILI9341::WHITE, ILI9341::BLACK);
  print("Idle", 112, 0, ILI9341::WHITE, ILI9341::BLACK);

  print("Recipe step:  1", 0, 24, ILI9341::WHITE, ILI9341::BLACK);
  
  print("Barrel pressure (BPA1): ", 0, 48, ILI9341::WHITE, ILI9341::BLACK);
  print("?????", 192, 48, ILI9341::WHITE, ILI9341::BLACK);
  print(" bar", 232, 48, ILI9341::WHITE, ILI9341::BLACK);

  // Command buttons
  ili9341.drawRectangle(18, 114, 85, 143, ILI9341::YELLOW);
  print("Start", 32, 121, ILI9341::WHITE, ILI9341::BLACK);

  ili9341.drawRectangle(108, 114, 175, 143, ILI9341::YELLOW);  
  print("Hold", 126, 121, ILI9341::WHITE, ILI9341::BLACK);

  ili9341.drawRectangle(198, 144, 266, 173, ILI9341::YELLOW);
  print("Stop", 216, 151, ILI9341::WHITE, ILI9341::BLACK);
  
  ili9341.drawRectangle(18, 174, 85, 203, ILI9341::YELLOW);
  print("Resume", 28, 181, ILI9341::WHITE, ILI9341::BLACK);

  ili9341.drawRectangle(108, 174, 175, 203, ILI9341::YELLOW);
  print("Reset", 122, 181, ILI9341::WHITE, ILI9341::BLACK);
  
}

/**
 *
 */
void HMI::updateHomeScreen()
{

  updateHomeScreenTouch();
  updateBarrelPressureText();
  updateRecipeStateText();
  updateRecipeStepText();
  updateAlarmIndicator();
  
}

/**
 *  @todo Fix hack of text whitespace padding.
 */
void HMI::updateRecipeStateText()
{

  const char* text = "";
  ILI9341::Color color = ILI9341::WHITE;

  switch (carbonation_recipe.getRecipeState()) {

  case CarbonationRecipe::RecipeState::IDLE:
    text  = "Idle     ";
    color = ILI9341::WHITE;
    break;
    
  case CarbonationRecipe::RecipeState::RESUMMING:
    text  = "Resumming";
    color = ILI9341::YELLOW;
    break;
        
  case CarbonationRecipe::RecipeState::EXECUTING:
    text  = "Executing";
    color = ILI9341::GREEN;
    break;
    
  case CarbonationRecipe::RecipeState::HOLDING:
    text  = "Holding  ";
    color = ILI9341::YELLOW;
    break;
    
  case CarbonationRecipe::RecipeState::HELD:
    text  = "Held     ";
    color = ILI9341::WHITE;
    break;
    
  case CarbonationRecipe::RecipeState::STOPPING:
    text  = "Stopping ";
    color = ILI9341::YELLOW;
    break;
    
  case CarbonationRecipe::RecipeState::STOPPED:
    text  = "Stopped  ";
    color = ILI9341::RED;
    break;
    
  case CarbonationRecipe::RecipeState::COMPLETE:
    text  = "Complete ";
    color = ILI9341::GREEN;
    break;
    
  case CarbonationRecipe::RecipeState::RESETTING:
    text  = "Resetting";
    color = ILI9341::YELLOW;
    break;
  }
  
  print(text, 112, 0, color, ILI9341::BLACK);
  
}

/**
 *  @todo Fix hardcoding.
 */
void HMI::updateRecipeStepText()
{

  char text[1 + 1];
  
  sprintf(text, "%d", carbonation_recipe.getRecipeStep());
  
  print(text, 112, 24, ILI9341::WHITE, ILI9341::BLACK);
  
}

/**
 *  @todo Fix hardcoding
 */
void HMI::updateBarrelPressureText()
{

  char text[5 + 1];

  sprintf(text, "%.3f", carbonator.getBPA1());
  
  print(text, 192, 48, ILI9341::WHITE, ILI9341::BLACK);

}


/**
 *  
 */ 
void HMI::updateAlarmIndicator()
{

  std::vector<const char*> active_alarms = alarm_system.getActiveAlarms();

  if (not active_alarms.empty() and not is_alarm_indicator_visible) {
    print(active_alarms.back(), 0, 72, ILI9341::WHITE, ILI9341::RED);
    is_alarm_indicator_visible = true;
  } else if (is_alarm_indicator_visible) {
    print("                                   ", 0, 72, ILI9341::WHITE,
          ILI9341::BLACK);
    is_alarm_indicator_visible = false;
  }
  
}

/**
 * This function updates and processes the current touch interaction state 
 * specifically for the home screen.
 *  @todo Fix buttons hardcoding
 */ 
void HMI::updateHomeScreenTouch()
{

  switch (touch_state) {

  case TouchState::IDLE:
    break;

  case TouchState::PRESSED:
    updateTouchPoint();
    break;

  case TouchState::RELEASED:

    // Start button press
    if (touch_point.x >= 18  and touch_point.x <= 85 and
        touch_point.y >= 114 and touch_point.y <= 143) {
      carbonation_recipe.start();
    }
    
    // Hold button press
    if (touch_point.x >= 108 and touch_point.x <= 175 and
        touch_point.y >= 114 and touch_point.y <= 143) {
      carbonation_recipe.hold();
    }

    // Stop button press
    if (touch_point.x >= 198 and touch_point.x <= 266 and
        touch_point.y >= 144 and touch_point.y <= 173) {
      carbonation_recipe.stop();
    }

    // Resume button press
    if (touch_point.x >= 18  and touch_point.x <= 85 and
        touch_point.y >= 174 and touch_point.y <= 203) {
      carbonation_recipe.resume();
    }

    // Reset button press
    if (touch_point.x >= 108 and touch_point.x <= 175 and
        touch_point.y >= 174 and touch_point.y <= 203) {
      carbonation_recipe.reset();
    }

    touch_state = TouchState::IDLE;
    
    break;
    
  }
  
}
