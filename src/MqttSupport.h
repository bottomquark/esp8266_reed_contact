/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _MQTT_SUPPORT_H_
#define _MQTT_SUPPORT_H_

#include <PubSubClient.h>

class MqttSupportClass
{
private:
  void connect();

public:
  void setup();
  void loop();
};

extern MqttSupportClass MqttSupport;

#endif