#include "Siren.h"

/**
 *  This constructor configures the PWM signal with the specified frequency
 *  and sets the initial duty cycle to 50%.
 *
 *  @note The signal is left suspended until the `activate` method is called.
 *
 *  @param on_actuating_signal_pin the pin connected to the siren's actuating signal.
 *  @param tone_frequency the initial frequency of the siren's tone in Hz.
 *  
 */
Siren::Siren(PinName on_actuating_signal_pin, float tone_frequency)
  : on_actuating_signal(on_actuating_signal_pin)
{

  // PWM configuration  
  on_actuating_signal.period(1.0 / tone_frequency);
  on_actuating_signal.write(0.5); // 50 % duty cycle
  on_actuating_signal.suspend();

}

/**
 *  Resumes the PWM signal, causing the siren to emit its tone.
 */
void Siren::activate()
{

  on_actuating_signal.resume();
  
}


/**
 *  Suspends the PWM signal, silencing the siren.
 */
void Siren::deactivate()
{

  on_actuating_signal.suspend();
    
}

/**
 *  Updates the period of the PWM signal to match the specified frequency.
 *  @note The siren must be active to configure the new tone.
 *
 *  @param frequency the newtone frequency in Hz.
 *  
 *  @pre frequency > 0 Hz
 */
void Siren::setToneFrequency(float frequency)
{

  on_actuating_signal.period(1.0 / frequency);
  
}
