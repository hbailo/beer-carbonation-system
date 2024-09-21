#include "PressureTransmitter.h"


PressureTransmitter::PressureTransmitter(PinName measured_pressure_signal_pin)
    : measured_pressure_signal(measured_pressure_signal_pin)
{
 
}


PressureTransmitter::operator float()
{

  return scale() ;
  
}


/** @todo Fix transmitter range hardcoding. In the current implementation it is
 * assumed that the connected transmitter sends a signal of 3.3 V when the
 * process pressure is 5 bar.
 *
 * @return pressure in pressure units.
*/
float PressureTransmitter::scale()
{

  return measured_pressure_signal.read_voltage() / 3.3 * 5.0 ;
  
}
