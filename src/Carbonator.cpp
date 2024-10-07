#include "Carbonator.h"
#include <cmath>

using namespace std::chrono ;


Carbonator::Carbonator()
  : qmb1(D2), maa1(D3), bpa1(A1)
{
  
}


/**
 *  @param[in] pressure the desired pressure in bar.
 *
 *  This method keeps the solenoid valve QMB1 open until the specified
 *  pressure is reached in BPA1. Then closes QMB1.
 *
 *  @return true if the specified pressure was reached, otherwise false.
 */
bool Carbonator::injectCO2(float pressure)
{
  
  bool done = bpa1 > pressure ;

  if (done) {
    qmb1.off_cmd = true ;
  } else {
    qmb1.on_cmd = true ;
  }

  execute() ;

  return done ;
  
}


/**
 *  This method keeps the agitator on until the CO2 dissolves completely.
 *  Complete dissolution is determined when the current sample and the sample
 *  from one second ago differ by less than 10 mbar.
 *
 *  @return true if the specified pressure was reached, otherwise false.
 *
 *  @todo Fix pressure threshold and sampling period hardcoding.
 */
bool Carbonator::dissolveCO2()
{

  bool done ;

  timer.start() ;

  if (duration<float>{timer.elapsed_time()}.count() > 1) {
    float current_bpa1_sample = bpa1 ;

    done = abs(current_bpa1_sample - last_bpa1_sample) < 0.01 ;

    if (done) {
      maa1.off_cmd = true ;
      last_bpa1_sample = 0 ;
      timer.stop() ;
      timer.reset() ;
      
    } else {
      maa1.on_cmd = true ;
      last_bpa1_sample = current_bpa1_sample ;
      timer.reset() ;
    }
    
  } else {
    done = false ;
  }

  execute() ;

  return done ;
  
}


/** */
void Carbonator::stop()
{

  qmb1.protection_off_cmd = true ;
  maa1.protection_off_cmd = true ;

  execute() ;
  
}


/**
 *  @return QMB1 pressure in bar.
 */
float Carbonator::getBPA1() noexcept
{

  return bpa1 ;
  
}


/**
 *  @todo complete doc.
 */
void Carbonator::execute()
{

  // QMB1 interlock logic

  // MAA1 interlock logic

  qmb1.execute() ;
  maa1.execute() ;
  
}
