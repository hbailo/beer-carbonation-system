#include "CarbonationRecipe.h"
#include "font.h"
#include "HMI.h"
#include "ILI9341.h"
#include "mbed.h"
#include <cstdint>
#include <system_error>

/**
 *
 */
HMI::HMI(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe)
  : carbonator(carbonator), carbonation_recipe(carbonation_recipe), ili9341(PB_5, PB_4, PB_3, PB_12, PC_7, PB_8, PA_15)
{

  initHomeScreen();
  
}

/**
 *
 */
void HMI::update()
{

  updateHomeScreen();
  
}

/**
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
 *
 */
void HMI::initHomeScreen()
{

  ili9341.fillScreen(ILI9341::Color::BLACK);
  
  print("Recipe state: ", 0, 0, ILI9341::WHITE, ILI9341::BLACK);
  print("Idle", 112, 0, ILI9341::WHITE, ILI9341::BLACK);

  print("Recipe step:  1", 0, 24, ILI9341::WHITE, ILI9341::BLACK);
  
  print("Barrel pressure (BPA1): ", 0, 48, ILI9341::WHITE, ILI9341::BLACK);
  print("?????", 192, 48, ILI9341::WHITE, ILI9341::BLACK);
  print(" bar", 232, 48, ILI9341::WHITE, ILI9341::BLACK);


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
 *  @todo Implement alarm indication support.
 */ 
void HMI::updateAlarmIndicator()
{

  // print("Alarm: Barrel overpressure (BPA1)", 0, 24, ILI9341::WHITE,
  //       ILI9341::RED);
  
}
