#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "ILI9341.h"
#include "mbed.h"
#include "XPT2046.h"

void handleOnTouchPressed();
void handleOnTouchReleased();
void calibrateTouchscreen(ILI9341& ili9341, XPT2046& xpt2046);

static bool touching = false;

int main()
{

  ILI9341 ili9341(PB_5, PB_4, PB_3, PB_12, PC_7, PB_8, PA_15);
  XPT2046 xpt2046(PE_14, PE_13, PE_12, PE_11, PE_15, handleOnTouchPressed, handleOnTouchReleased);
  
  uint16_t x; 
  uint16_t y;

  calibrateTouchscreen(ili9341, xpt2046);
  
  while (true) {
  
    if (touching) {
      xpt2046.getTouchPoint(x, y);
      printf("x = %d | y = %d\n", x, y);
    }

    ThisThread::sleep_for(1ms);
  }

  return EXIT_SUCCESS;
  
}

void calibrateTouchscreen(ILI9341& ili9341, XPT2046& xpt2046)
{

  printf("Calibrating...\n");
  
  uint16_t x;
  uint16_t y;

  ili9341.fillScreen(ILI9341::BLACK);

  // Point 1
  double x_mean_0 = 0;
  double y_mean_0 = 0;
  
  printf("Press and hold white píxel...\n");
  ili9341.setPixel(50, 40, ILI9341::WHITE);

  while (not touching) {
    ThisThread::sleep_for(1s);
  }
  
  for (uint16_t i = 0; i < 1000; ++i) {
    xpt2046.getTouchPoint(x, y);
    
    x_mean_0 += x;
    y_mean_0 += y;
    
    printf("%d,%d\n", x, y);
    
    if (!touching) {
      printf("Got up prematurely, restart.\n");
      return;
    }
    
  }
  
  x_mean_0 /= 1000;
  y_mean_0 /= 1000;

  printf("release.\n");

  ili9341.setPixel(50, 40, ILI9341::BLACK);

  while (touching) {
    ThisThread::sleep_for(1s);
  }

  // Point 2
  double x_mean_1 = 0;
  double y_mean_1 = 0;
  
  printf("Press and hold white píxel...\n");  
  ili9341.setPixel(260, 200, ILI9341::WHITE);

  while (not touching) {
    ThisThread::sleep_for(1s);
  }
  
  for (uint16_t i = 0; i < 1000; ++i) {
    xpt2046.getTouchPoint(x, y);
    
    x_mean_1 += x;
    y_mean_1 += y;

    printf("%d,%d\n", x, y);
    
    if (!touching) {
      printf("Got up prematurely, restart.\n");
      return;
    }
    
  }
  
  x_mean_1 /= 1000;
  y_mean_1 /= 1000;

  printf("release.\n");

  ili9341.setPixel(260, 200, ILI9341::BLACK);

  while (touching) {
    ThisThread::sleep_for(1s);
  }
  
  double mx = (260.0 - 50.0) / (x_mean_1 - x_mean_0);
  double bx = 50 - mx * x_mean_0;
  
  printf("mx = %.6f\n", mx);
  printf("bx = %.6f\n", bx);
  
  double my = (200.0 - 40.0) / (y_mean_1 - y_mean_0);
  double by = 40.0 - my * y_mean_0;
  
  printf("my = %.6f\n", my);
  printf("by = %.6f\n", by);
  
  printf("Done.\n");
  
}

void handleOnTouchPressed()
{

  touching = true;
  
}

void handleOnTouchReleased()
{

  touching = false;

}
