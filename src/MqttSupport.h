/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#ifndef _MQTT_SUPPORT_H_
#define _MQTT_SUPPORT_H_

#include <PubSubClient.h>
#include <elapsedMillis.h>

#ifndef MQTT_CLIENT_ID
#define MQTT_CLIENT_ID "esp8266"
#endif

#ifndef MQTT_HOST
#define MQTT_HOST "127.0.0.1"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef MQTT_TOPIC_PUB
#define MQTT_TOPIC_PUB "data/esp8266"
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