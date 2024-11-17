#include "XPT2046.h"
#include <cstdint>

XPT2046::XPT2046(PinName mosi_pin, PinName miso_pin, PinName sclk_pin, PinName cs_pin, PinName penirq_pin, Callback<void()> onTouchPressed, Callback<void()> onTouchReleased)
  : spi(mosi_pin, miso_pin, sclk_pin), cs(cs_pin, true), penirq(penirq_pin, PullNone)
{

  // SPI configuration
  spi.format(8, 0); // SPI frame of 8 bits and clock polarity and phase mode 0.
  spi.frequency(1000000);

  // On power on initialization
  cs = false;
  spi.write(POWER_DOWN_BETWEEN_CONVERSIONS);
  cs = true;
  
  // Interrupts for touch events handling
  penirq.fall(onTouchPressed);
  penirq.rise(onTouchReleased);
  
}

void XPT2046::getTouchPoint(uint16_t& x, uint16_t& y)
{

  char cmd_buf[4] = {XPT2046::READ_X_POSITION, 0x00, 0x00, XPT2046::READ_Y_POSITION};
  char loc_buf[6];

  cs = false;
  spi.write(cmd_buf, 4, loc_buf, 6);
  cs = true;

  x = (static_cast<uint16_t>(loc_buf[1]) << 5) |
      (static_cast<uint16_t>(loc_buf[2]) >> 3);

  y = (static_cast<uint16_t>(loc_buf[4]) << 5) |
      (static_cast<uint16_t>(loc_buf[5]) >> 3);
}

/**
 * @return true if the screen is being touched, false otherwise.
 */
bool XPT2046::isTouched()
{

  return penirq.read() ? false : true;
  
}
