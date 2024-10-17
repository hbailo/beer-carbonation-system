#ifndef PRESSURE_TRANSMITTER__H
#define PRESSURE_TRANSMITTER__H

#include "mbed.h"

/**
 *  @brief Pressure transmitter module.
 */
class PressureTransmitter
{

public:
  /** @brief Constructs the transmitter module with the specified AI pin. */
  PressureTransmitter(PinName analog_input_pin);

  /** @brief Returns the scaled measured value. */
  operator float();
  
private:
  /** @brief Analog in signal */
  AnalogIn pressure_signal;

  /** @brief Scales the measured voltage signal to pressure units. */
  float scale();
  
} ;

#endif
