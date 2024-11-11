#ifndef XPT2046__H
#define XPT2046__H

#include "mbed.h"

/**
 *  @brief XPT2046 hardware driver.
 *
 *  The XPT2046 is a 4-wire resistive touch screen controller that incorporates
 *  a 12-bit 125 ksamples/s SAR type A/D converter.
 *
 *  @note In the official documentation the pins are labeled in a manner
 *  inconsistent with the SPI protocol, the following mapping was performed to
 *  improve understanding:
 *  - DOUT = SDO (originally MISO) 
 *  - DIN  = SDI (originally MOSI)
 *  - DCLK = SCKL
 *  
 *  References:
 *  [1] SHENZHEN XPTEK TECHNOLOGY CO. - XPT2046 Touch Screen Controller Data Sheet - Version 2007.5.
 */
class XPT2046 {

public:
  /** @brief Initializes the hardware. */
  XPT2046(PinName mosi_pin, PinName miso_pin, PinName sclk_pin, PinName cs_pin, PinName penirq_pin, Callback<void()> onTouchPressed = nullptr, Callback<void()> onTouchReleased = nullptr);

  /** @brief Returns the touch point location as (x, y) coordinates, measured in LSB (Least Significant Bit) counts. */
  void getTouchPoint(uint16_t& x, uint16_t& y);
  
  /** @brief Checks if the screen is currently being touched. */
  bool isTouched();
  
private:
  /** @brief SPI connection handler. */
  SPI spi;

  /** @brief SPI chip select signal. */
  DigitalOut cs;

  /** @brief Touch interrupt signal. @note Is active low and digital input must be floating.*/
  InterruptIn penirq;
  
  /** @brief Hardware commands. @note Each member is a Control Byte, see [1] section "Digital Interface". */
  enum Command : uint8_t {
    POWER_DOWN_BETWEEN_CONVERSIONS = 0x80,
    READ_X_POSITION = 0xD0, // Acquire X + 12 bits resolution + differential reference + power down between conversions.
    READ_Y_POSITION = 0x90  // Acquite Y + 12 bits resolution + differential reference + power down between conversions.
  };
  
};

#endif
