#ifndef HMI_DRIVER__H
#define HMI_DRIVER__H

#include "mbed.h"

#define HMI_HELP_PROMPT "Press:\n  1. To start the carbonation process.\n  2. To stop the carbonation process. \n  3. To reset the carbonation process."

class HMIDriver
{

public:
    
  enum UserCommand {
    NONE,
    START_CARBONATION_PROCEDURE,
    STOP_CARBONATION_PROCEDURE,
    RESET_CARBONATION_PROCEDURE
  } ;
  
  HMIDriver() ;
  
  UserCommand getUserCommand() ;

private:
  
  /** UART USB connection */
  UnbufferedSerial uart_usb ;
  
} ;

#endif
