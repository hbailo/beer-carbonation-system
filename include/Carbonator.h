#ifndef CARBONATOR__H
#define CARBONATOR__H

#include "mbed.h"
#include "OnOffMotor.h"
#include "PressureTransmitter.h"
#include "SolenoidValve.h"


/**
 *  @brief Carbonator equipment module.
 */
class Carbonator
{

public:
  
  Carbonator() ;
  
  /** \brief Injects CO2 up to pressure. */
  bool injectCO2(float pressure) ;

  /** \brief Dissolves CO2 in the beer. */
  bool dissolveCO2() ;

  /** \brief Stops the equipment. */
  void stop() ;

  /** \brief Returns the QMB1 pressure.*/
  float getBPA1() noexcept ;

private:
  
  void execute() ;

  /** CO2 shut off valve. */
  SolenoidValve qmb1 ;

  /** Agitator electric motor. */
  OnOffMotor maa1 ;

  /** Beer barrel pressure transmitter. */
  PressureTransmitter bpa1 ;

  /** Members used in dissolverCO2 */
  Timer timer ;
  float last_bpa1_sample = 0.0 ;
  
} ;
  
#endif
