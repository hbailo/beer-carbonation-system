#include "HMIDriver.h"
#include <cstring>

HMIDriver::HMIDriver()
  : uart_usb(USBTX, USBRX, 9600)
{

  uart_usb.write(HMI_HELP_PROMPT, strlen(HMI_HELP_PROMPT)) ;
    
}

HMIDriver::UserCommand HMIDriver::getUserCommand()
{

  char receivedChar = '\0' ;
  
  if(uart_usb.readable()) {
    uart_usb.read(&receivedChar, 1) ;
    
    switch (receivedChar) {
    case '1':
      return START_CARBONATION_PROCEDURE;
      
    case '2':
      return STOP_CARBONATION_PROCEDURE;
      
    case '3':
      return RESET_CARBONATION_PROCEDURE;
      
    default:
      return NONE ;
    }
    
  }

  return NONE;
  
}
