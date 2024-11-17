#ifndef ILI9341__H
#define ILI9341__H

#include "mbed.h"
#include <cstdint>

/**
 *  @brief ILI9341 hardware driver.
 *
 *  This class use the 4 wire SPI communication interface, so external pins
 *  IM[3:0] = [IM3, IM2, IM1, IM0] = ['1' '1' '1' '0'].
 *
 *  @note In the official documentation the pins are labeled in a manner
 *  inconsistent with the SPI protocol, the following mapping was performed to
 *  improve understanding:
 *  - SDA = SDI (MOSI)
 *  - SDO = SDO (MISO)
 *  - SCL = SCKL
 *  - CSX = CS
 *
 *  References:
 *  [1] ILI TECHNOLOGY CORP. - a-Si TFT LCD Single Chip Driver
 *  240RGBx320 Resolution and 262K color specification - Version 1.11, Document number ILI9341_DS_V1.11.pdf
 */
class ILI9341 {

public:
  /** @brief Colors 16 bits codes. */
  enum Color16Bits : uint16_t {
    BLACK  = 0x0000,
    GREEN  = 0x07E0,
    RED    = 0xF800,
    YELLOW = 0xFFE0,
    WHITE  = 0XFFFF
  };
  
  using Color = Color16Bits;

  /** @brief Initializes the ILI9341 hardware driver. */
  ILI9341(PinName mosi_pín, PinName miso_pin, PinName sckl_pin, PinName cs_pin,
          PinName dcx_pin, PinName resx_pin, PinName backlight_pin);

  /** @brief Sets pixel with color. */
  void setPixel(uint16_t x, uint16_t y, Color color);
  
  /** @brief Draws an image. */
  void drawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                 const Color* data);

  /** @brief Fills the screen with color. */
  void fillScreen(Color color);

  /** @brief Draws an horizontal line. */
  void drawHLine(uint16_t y, uint16_t x0, uint16_t x1, Color color);

  /** @brief Draws a vertical line. */  
  void drawVLine(uint16_t x, uint16_t y0, uint16_t y1, Color color);

  /** @brief Draws a rectangle */
  void drawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color color);
  
private:
  /** @brief SPI connection handler. */
  SPI spi;

  /** @brief SPI chip select signal. */
  DigitalOut cs;
  
  /** @brief DCX signal. */
  DigitalOut dcx;

  /** @brief RESX signal. */
  DigitalOut resx;

  /** @brief Backlight signal. */
  DigitalOut backlight;
  
  /** @brief Hardware commands. */
  enum Command : uint8_t {
    SLEEP_OUT = 0x11,
    DISPLAY_ON = 0x29,
    COLUMN_ADDRESS_SET = 0x2A, // CASET
    PAGE_ADDRESS_SET = 0x2B,   // PASET
    MEMORY_WRITE = 0x2C,       // RAMWR
    MEMORY_ACCESS_CONTROL = 0x36, // MADCTL                             
    PIXEL_FORMAT_SET = 0x3A    // COLMOD
  };

  /** @brief Writes command to hardware. */
  void writeCommand(Command cmd);

  /** @brief Writes a command parameter (byte) to hardware. */
  void writeParameter(uint8_t parameter);

  // TODO: document.
  void setPageAddress(uint16_t sp, uint16_t ep);
  void setColumnAddress(uint16_t sc, uint16_t ec);
  void setMemoryAccessControl(uint8_t parameter);
  void exitSleepMode();
  void turnDisplayOn();
  void reset();
  void powerOn();
  void setPixelFormat(uint8_t parameter);
  void setFrameMemoryAreaAddress(uint16_t sc, uint16_t ec, uint16_t sp, uint16_t ep);
  void writeFrameMemoryArea(const Color* data, uint32_t data_length);
  void writeCommand(uint8_t cmd);

};

#endif
