#include <cstdio>
#include <cstring>
#include "CarbonationRecipe.h"
#include "Carbonator.h"
#include "mbed.h"
#include "SupervisoryComputer.h"

/**
 *
 */
SupervisoryComputer::SupervisoryComputer(Carbonator& carbonator, CarbonationRecipe& carbonation_recipe)
  : carbonator(carbonator), carbonation_recipe(carbonation_recipe), uart(USBTX, USBRX, 9600)
{

  uart.write(USAGE_INFO, strlen(USAGE_INFO));
  
}

/**
 *  @todo Refactorize and fix commands hardcoding.
 */
void SupervisoryComputer::update()
{

  char cmd;
  
  if(uart.readable()) {
    uart.read(&cmd, 1);

    switch (cmd) {
    case '1':
      carbonation_recipe.start();
      break;
      
    case '2':
      carbonation_recipe.stop();
        break;
      
    case '3':
      carbonation_recipe.hold();
      break;
      
    case '4':
      carbonation_recipe.resume();
      break;

    case '5':
      carbonation_recipe.reset();
      break;

    case 'r':
      reporting_state = ReportingState::REPORTING;
      break;

    case 'R':
      reporting_state = ReportingState::IDLE;
      break;

    case 'h':
      uart.write(USAGE_INFO, strlen(USAGE_INFO));
      break;

    default:
      break;
    }
    
  }

  if (reporting_state == ReportingState::REPORTING) {
    char report[14 + 1];

    sprintf(report, "{\"qmb1\":%.3f}", carbonator.getBPA1()); // NOTE: report is in JSON format.
    
    uart.write(report, strlen(report));
  }
  
}
