/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _WIFI_SUPPORT_H_
#define _WIFI_SUPPORT_H_

#include <ESP8266WiFi.h>
#include <elapsedMillis.h>

class WiFiSupportClass
{
private:
  elapsedMillis sinceReconnect;
  uint32_t reconnectionAttempts;
  void connect();

public:
  void setup();
  void loop();
  bool isConnected();
};

extern WiFiSupportClass WiFiSupport;

#endif