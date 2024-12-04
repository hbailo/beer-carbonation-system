#include "Siren.h"

/**
 *
 */
Siren::Siren(PinName on_actuating_signal_pin, float tone_frequency)
  : on_actuating_signal(on_actuating_signal_pin)
{

  // PWM configuration  
  on_actuating_signal.period(1.0 / tone_frequency);
  on_actuating_signal.write(0.5); // Duty cycle @ 50 %
  on_actuating_signal.suspend();

}

/**
 *
 */
void Siren::activate()
{

  on_actuating_signal.resume();
  
}


/**
 *
 */
void Siren::deactivate()
{

  on_actuating_signal.suspend();
    
}

/**
 *
 */
void Siren::setToneFrequency(float frequency)
{

  on_actuating_signal.period(1.0 / frequency);
  
}
