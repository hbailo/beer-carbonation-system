#ifndef SIREN_H
#define SIREN_H

#include "mbed.h"

class Siren {

public:
  /** @brief Initializes the siren. */
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
