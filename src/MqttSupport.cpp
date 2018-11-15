/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "MqttSupport.h"

WiFiClient wifiClient;
PubSubClient mqttCient;

void MqttSupportClass::setup()
{
    // Set-Up WiFi connection.
    WiFiSupport.setup();

    // Initialize MQTT connection.
    mqttCient.setClient(wifiClient);
    mqttCient.setServer(MQTT_HOST, MQTT_PORT);
    sinceReconnect = 10000;
    this->connect();
}

void MqttSupportClass::loop()
{
    // Check WIFI connection.
    WiFiSupport.loop();

    this->connect();
}

void MqttSupportClass::connect()
{
    if (WiFiSupport.isConnected() && !this->isConnected() && sinceReconnect >= 10000)
    {
        Log.trace("Connect to MQTT broker %s:%d with clientId %s. Current client state: %d. Connection attempts: %d",
                  MQTT_HOST, MQTT_PORT, MQTT_CLIENT_ID, mqttCient.state(), ++reconnectionAttempts);
        mqttCient.connect(MQTT_CLIENT_ID); // Try to connect to the MQTT broker
        sinceReconnect = 0;
    }
}

bool MqttSupportClass::isConnected()
{
    return mqttCient.connected();
}

bool MqttSupportClass::publish(String message)
{
    return mqttCient.publish(MQTT_TOPIC_PUB, message.c_str());
}

MqttSupportClass MqttSupport = MqttSupportClass();