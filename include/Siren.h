#ifndef SIREN_H
#define SIREN_H

#include "mbed.h"

/**
 * @brief A class to control a siren using a PWM output signal.
 * 
 * This class allows for controlling the activation and deactivation of a siren
 * as well as setting its tone frequency. It uses the mbed `PwmOut` class
 * to generate the required PWM signal.
 */
class Siren {

public:
  /** @brief Constructs a Siren object and initializes the PWM signal. */
  Siren(PinName on_actuating_signal_pin, float tone_frequency);

  /** @brief Activates the siren. */
  void activate();

  /** @brief Deactivates the siren. */
  void deactivate();

  /** @brief Sets the tone frequency. */
  void setToneFrequency(float frequency);

private:
  /** @brief On actuating signal. */
  PwmOut on_actuating_signal;
  
};

#endif
