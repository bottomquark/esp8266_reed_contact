/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _WIFI_SUPPORT_H_
#define _WIFI_SUPPORT_H_

#include <ESP8266WiFi.h>

class WiFiSupportClass
{
private:
  void connect();

public:
  void setup();
  void loop();
};

extern WiFiSupportClass WiFiSupport;

#endif