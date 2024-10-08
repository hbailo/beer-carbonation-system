#ifndef CARBONATOR__H
#define CARBONATOR__H

#include "mbed.h"
#include "OnOffMotor.h"
#include "PressureTransmitter.h"
#include "SolenoidValve.h"

/**
 *  @brief Carbonator unit equipment.
 */
class Carbonator
{

public:
  
  /** @brief Initializes carbonator unit. */
  Carbonator() ;
  
  /** @brief Injects CO2 up to pressure. */
  bool injectCO2(float pressure) ;

  /** @brief Dissolves CO2 in the beer. */
  bool dissolveCO2() ;

  /** @brief Stops the unit equipment. */
  void stop() ;

  /** @brief Returns the beer barrel pressure.*/
  float getBPA1() noexcept ;

private:
  
  void execute() ;

  State state;
  
  /** @brief CO2 shut off valve. */
  SolenoidValve qmb1 ;

  /** @brief Barrel shaker electric motor. */
  OnOffMotor maa1 ;

  /** @brief Beer barrel pressure transmitter. */
  PressureTransmitter bpa1 ;

  /** Members used in dissolveCO2() algorithm*/
  Timer timer ;
  float last_bpa1_sample = 0.0 ;
  
} ;
  
#endif
