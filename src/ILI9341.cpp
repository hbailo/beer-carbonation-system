#include "ILI9341.h"
#include "mbed.h"
#include <cstdint>

/**

 * ILI9341 is initialized with the following parametrization:
 * - 16 bits colors
 * - Memory access control: BGR to RGB.
 */
ILI9341::ILI9341(PinName mosi_pin, PinName miso_pin, PinName sckl_pin, PinName cs_pin, PinName dcx_pin, PinName resx_pin)
  : spi(mosi_pin, miso_pin, sckl_pin), cs(cs_pin, false), dcx(dcx_pin, false), resx(resx_pin, true)
{

  spi.format(8, 0);        // SPI frame of 8 bits and clock polarity and phase mode 0.
  spi.frequency(10000000); // 1 MHz
  
  powerOn();

}

void ILI9341::setPixel(uint16_t x, uint16_t y, Color color)
{
  
  setFrameMemoryAreaAddress(x, x, y, y);
  
  writeFrameMemoryArea(&color, 1);

}

/**
 *  A frame area is a rectangular area of the display that is specified from its pixel
 *  of origin and extends downward and to the right.
 *  The pixel of origin is the one corresponding to the upper left corner of the frame area.
 *  The frame area data is passed as an array of colors where the elements correspond to the
 *  path from left to right and top to bottom of the pixels of the frame area, starting with
 *  the pixel of origin.
 *
 *  Frame area  <--  Frame area data array
 *  [A, B, C]         [A, B, C, D, E, F]
 *  [D, E, F]
 * 
 *  @pre This function does NOT check arguments size consistency, i.e. data array can be longer or shorter than the specified frame area. It is up to the user to check the sizes.
 *  
 *  @param x the x pixel coordinate of the upper-left corner of the frame area.
 *  @param y the y pixel cooordinate of the upper-left corner of the frame area.
 *  @param width the frame area width in pixels.
 *  @param height the frame height area in pixels.
 *  @param data the frame area color data.
 */ 
void ILI9341::drawImage(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const Color* data)
{
  
  setFrameMemoryAreaAddress(x, x + width - 1, y, y + height - 1);
  writeFrameMemoryArea(data, width * height);

}
 
/** @brief Fills the screen with color. 
 *
 *  @todo Refactorize, improve performance and FIX display dimensions hardcoding.
*/
void ILI9341::fillScreen(Color color)
{
  
  Color patch[2 * 320];
  
  for (uint16_t i = 0; i < 2 * 320; ++i) {
      patch[i] = color;
  }
  
  for (uint16_t y = 0; y < 320; y += 2) {

    for (uint16_t x = 0; x < 240; x += 240) {
      drawImage(x, y, 320, 2, patch);
    }

  }

}

/**
 *  @note The line includes the endpointes, i.e. extends over pixels (@p x0, @p y)
 *  to (@p x1, @p y). For example if @p x0 = 0 and @p x1 = 2, then pixels
 *  (0, @p y), (1, @p y), (2, @p y) are setted.
 *
 *  @param[in] x the x pixel coordinate of the left line endpoint.
 *  @param[in] y the y pixel coordinate of the left line endpoint.
 *  @param[in] length the length in pixels of the line.
 *
 *  @pre @p x0 ≤ @p x1
 *
 *  @todo Refactorize, improve performance and FIX display dimensions hardcoding.
*/
void ILI9341::drawHLine(uint16_t y, uint16_t x0, uint16_t x1, Color color)
{
  
  Color buf[320]; // TODO: This buffer is used in many functions, maybe it can be part of the class.

  uint16_t length = x1 - x0 + 1;
  
  for (uint16_t i = 0; i < length; ++i) {
      buf[i] = color;
  }

  setFrameMemoryAreaAddress(x0, x1, y, y);
  writeFrameMemoryArea(buf, length);
  
}

/**
 *  @note The line includes the endpoints, i.e. extends over pixels (@p x, @p y0)
 *  to (@p x, @p y1). For example if @p y0 = 0 and @p y1 = 2, then pixels
 *  (@p x, 0), (@p x, 1), (@p x, 2) are setted.
 *
 *  @param[in] x the x pixel coordinate of the left line endpoint.
 *  @param[in] y the y pixel coordinate of the left line endpoint.
 *  @param[in] length the length in pixels of the line.
 *
 *  @pre @p y0 ≤ @p y1
 *
 *  @todo Refactorize, improve performance and FIX display dimensions hardcoding.
*/
void ILI9341::drawVLine(uint16_t x, uint16_t y0, uint16_t y1, Color color)
{
  
  Color buf[320]; // TODO: This buffer is used in many functions, maybe it can be part of the class.

  uint16_t length = y1 - y0 + 1;
  
  for (uint16_t i = 0; i < length; ++i) {
      buf[i] = color;
  }  

  setFrameMemoryAreaAddress(x, x, y0, y1);
  writeFrameMemoryArea(buf, length);
  
}

void ILI9341::drawRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Color color)
{

  drawHLine(y0, x0, x1, color); // Bottom edge
  drawHLine(y1, x0, x1, color); // Top    edge 
  drawVLine(x0, y0, y1, color); // Left   edge
  drawVLine(x1, y0, y1, color); // Right  edge

}

/** @brief Fills the screen with color. 
 *
 *  @todo Refactorize, improve performance and FIX display dimensions hardcoding.
*/
void ILI9341::powerOn()
{
  
  ThisThread::sleep_for(1ms); // NOTE: Duration of "After Powered ON" reset, see [1] page 228.

  reset(); // Hardware reset

  setMemoryAccessControl(0xE8); // MX | MY | MV | BGR
  setPixelFormat(0x05);         // MCU 16 bits pixel colors
  
  exitSleepMode();
 
  turnDisplayOn();

}


/** 
 *  @brief Performs a hardware reset.
 *  @note This method has an execution time of approximately 121 ms.
 */
void ILI9341::reset()
{

  resx = false;
  ThisThread::sleep_for(1ms); // NOTE: Minimum reset pulse duration, see [1] page 230.
  resx = true;
  ThisThread::sleep_for(120ms); // NOTE: Duration of hardware resseting, see [1] page 230, NOTE 3.

}

void ILI9341::exitSleepMode()
{

  writeCommand(SLEEP_OUT);
  ThisThread::sleep_for(5ms); // NOTE: Time for the supply voltages and clock
                              // circuits to stabilize, see [1] page 101.  
}

void ILI9341::setPixelFormat(uint8_t parameter)
{

  writeCommand(PIXEL_FORMAT_SET);
  writeParameter(parameter);
  
}

void ILI9341::turnDisplayOn()
{

  writeCommand(DISPLAY_ON);
  
}

void ILI9341::writeFrameMemoryArea(const Color* data, uint32_t data_length)
{

  writeCommand(MEMORY_WRITE);

  for (uint32_t i = 0; i < data_length; ++i) {
    writeParameter(data[i] >> 8);     // NOTE: if 18 bits colors need to be implemented
    writeParameter(data[i] & 0x00FF); // then 3 bytes need to be sent.
  }
  
}

void ILI9341::setFrameMemoryAreaAddress(uint16_t sc, uint16_t ec, uint16_t sp, uint16_t ep)
{

  setColumnAddress(sc, ec);
  setPageAddress(sp, ep);

}

/**
 *  Set the column range of frame memory where MCU can access.
 *
 *  Parameter ranges:
 *
 *  If display is in normal mode (MADCTL[5] = '0'):
 *    0 < sc < 239
 *    0 < ec < 319
 *
 *  If display is in reverse mode (MADCTL[5] = '1'):
 *    0 < sc < 319
 *    0 < ec < 239
 *
 *  @note Parameters out of range will be ignored.
 *
 *  @param[in] sc start column line number.
 *  @param[in] ec end column line number.
 */
void ILI9341::setColumnAddress(uint16_t sc, uint16_t ec)
{

  writeCommand(COLUMN_ADDRESS_SET);
  writeParameter(sc >> 8);
  writeParameter(sc & 0x00FF);
  
  writeParameter(ec >> 8);
  writeParameter(ec & 0x00FF);
  
}

/**
 *  Set the page range of frame memory where MCU can access.
 *
 *  Parameter ranges:
 *
 *  If display is in normal mode (MADCTL[5] = '0'):
 *    0 < sp < 239
 *    0 < ep < 319
 *
 *  If display is in reverse mode (MADCTL[5] = '1'):
 *    0 < sp < 319
 *    0 < ep < 239
 *
 *  @note Parameters out of range will be ignored.
 *
 *  @param[in] sp start page line number.
 *  @param[in] ep end page line number.
 */
void ILI9341::setPageAddress(uint16_t sp, uint16_t ep)
{

  writeCommand(PAGE_ADDRESS_SET);
  writeParameter(sp >> 8);
  writeParameter(sp & 0x00FF);
  
  writeParameter(ep >> 8);
  writeParameter(ep & 0x00FF);

}

void ILI9341::writeCommand(uint8_t cmd)
{

  dcx = false;

  spi.write(cmd);

}

void ILI9341::writeCommand(Command cmd)
{

  dcx = false;

  spi.write(cmd);
  
}

void ILI9341::writeParameter(uint8_t data)
{

  dcx = true;

  spi.write(data);

}

void ILI9341::setMemoryAccessControl(uint8_t parameter) {

  writeCommand(MEMORY_ACCESS_CONTROL);
  writeParameter(parameter);
  
}
