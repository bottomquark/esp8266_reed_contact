/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "MqttSupport.h"

WiFiClient wifiClient;
PubSubClient mqttCient;

void visualizeNetworkConnectionLost();

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
    visualizeNetworkConnectionLost();
}

void MqttSupportClass::connect()
{
    if (WiFiSupport.isConnected() && !this->isConnected() && sinceReconnect >= 10000)
    {
        Log.trace("Connect to MQTT broker %s:%d with clientId %s. Current client state: %d. Connection attempts: %d",
                  MQTT_HOST, MQTT_PORT, MQTT_CLIENT_ID, mqttCient.state(), ++reconnectionAttempts);
        // Try to connect to the MQTT broker
#if defined(MQTT_USER) && defined(MQTT_PASS)
        mqttCient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS);
#else
        mqttCient.connect(MQTT_CLIENT_ID);
#endif
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

void visualizeNetworkConnectionLost()
{
    if (!WiFiSupport.isConnected() || !MqttSupport.isConnected())
    {
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
    }
    digitalWrite(LED_BUILTIN, HIGH);
}

MqttSupportClass MqttSupport = MqttSupportClass();