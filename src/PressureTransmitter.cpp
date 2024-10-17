#include "PressureTransmitter.h"


PressureTransmitter::PressureTransmitter(PinName analog_input_pin)
    : pressure_signal(analog_input_pin)
{
 
}


PressureTransmitter::operator float()
{

  return scale();
  
}


/** @todo Fix transmitter range hardcoding. In the current implementation it is
 * assumed that the connected transmitter sends a signal of 3.3 V when the
 * process pressure is 5 bar.
 *
 * @return pressure in pressure units.
*/
float PressureTransmitter::scale()
{

  return pressure_signal.read() * 5.0;
  
}
