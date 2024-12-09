#include "ESP01.h"
#include <cstdint>

/**
 *
 */
ESP01::ESP01(const char* ssid, const char* password)
  : uart(PD_5, PD_6, 115200), enable(PD_7, true), has_pending_request(false)
{

  ThisThread::sleep_for(250ms);
  
  setStationMode();

  ThisThread::sleep_for(10ms);
    
  connectToAccessPoint(ssid, password);

  ThisThread::sleep_for(10s);
  
  setMultipleConnectionsMode();

  ThisThread::sleep_for(10ms);
  
  openHTTPPort();
  
  ThisThread::sleep_for(20ms);

  // Flush serial buffer for correct initialization
  char c;
  while (uart.readable()) {
    uart.read(&c, 1);
  }
  
  uart.sigio([this]() { handleOnRx(); });
  
}

/**
 *  @todo Fix connection id hardcoding.
 */
void ESP01::handleOnRx()
{

  new_data_on_rx = true;

  uart.sigio(nullptr);  
}

/**
 *  @todo Fix connection id hardcoding.
 */
bool ESP01::hasPendingRequest()
{

  char c;

  if (not has_pending_request and uart.readable()) {
    uart.read(&c, 1);

    if (c == '0') {
      has_pending_request = true;
    }
    
  }

  new_data_on_rx = false;
  
  return has_pending_request;
  
}

/**
 *  @todo Fix connection id hardcoding.
 */
void ESP01::sendResponse(const char* response)
{

  if (has_pending_request) {
    char command[26];

    sprintf(command, "AT+CIPSEND=%c,%d\r\n", '0', strlen(response));

    uart.write(command, strlen(command));
  
    ThisThread::sleep_for(10ms);

    uart.write(response, strlen(response));

    // Flush serial buffer for correct initialization
    char c;
    while (uart.readable()) {
      uart.read(&c, 1);
    }

    uart.sigio([this]() { handleOnRx(); });
    has_pending_request = false;
  }
  
}

void ESP01::closeConnection(int8_t connection_id)
{

  char command[25];

  sprintf(command, "AT+CIPCLOSE=%d\r\n", connection_id);

  uart.write(command, strlen(command));

}

/**
 *
 */
void ESP01::setStationMode()
{

  const char* COMMAND = "AT+CWMODE=1\r\n";
  
  uart.write(COMMAND, strlen(COMMAND));

}

/**
 *
 */
void ESP01::setMultipleConnectionsMode()
{

  const char *COMMAND = "AT+CIPMUX=1\r\n";

  uart.write(COMMAND, strlen(COMMAND));

}

/**
 *
 */
void ESP01::getIPAddress()
{

  const char *COMMAND = "AT+CIFSR\r\n";

  uart.write(COMMAND, strlen(COMMAND));
  
}

/**
 *
 */
void ESP01::connectToAccessPoint(const char* ssid, const char* password)
{

  const char* COMMAND = "AT+CWJAP=\"";

  uart.write(COMMAND, strlen(COMMAND));
  uart.write(ssid, strlen(ssid));
  uart.write("\",\"", 3);
  uart.write(password, strlen(password));
  uart.write("\"\r\n", 3);
  
}

/**
 *
 */
void ESP01::openHTTPPort()
{

  const char* COMMAND = "AT+CIPSERVER=1,80\r\n";

  uart.write(COMMAND, strlen(COMMAND));
  
}
