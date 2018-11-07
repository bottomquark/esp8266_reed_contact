/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _MQTT_SUPPORT_H_
#define _MQTT_SUPPORT_H_

#include <PubSubClient.h>
#include <elapsedMillis.h>

#ifndef MQTT_KEEPALIVE
#define MQTT_KEEPALIVE 900
#endif

class MqttSupportClass
{
private:
  elapsedMillis sinceReconnect;
  uint32_t reconnectionAttempts;
  void connect();

public:
  void setup();
  void loop();
  bool isConnected();
  bool publish(String message);
};

extern MqttSupportClass MqttSupport;

#endif