#ifndef ESP_01_H
#define ESP_01_H

#include "mbed.h"

/**
 *
 */
class ESP01 {

public:
  /** @brief Initializes ESP01 hardware. */
  ESP01(const char* ssid, const char* password);

  /** */
  void sendResponse(const char* response);
  bool hasPendingRequest();
  
private:
  /** @brief UART endpoint. */
  BufferedSerial uart;

  /** @brief Enable signal. */
  DigitalOut enable;

  /** */
  bool new_data_on_rx;
  bool has_pending_request;

  void closeConnection(int8_t connection_id);
  void setStationMode();
  void connectToAccessPoint(const char* ssid, const char* password);
  void setMultipleConnectionsMode();
  void openHTTPPort();
  void getIPAddress();
  void handleOnRx();
  
};

#endif
