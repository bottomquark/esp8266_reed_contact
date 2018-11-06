/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "MqttSupport.h"
#include "Config.h"

static String clientId = "ESP8266Client";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void MqttSupportClass::setup()
{
    // Set-Up WiFi connection.
    WiFiSupport.setup();

    // Initialize MQTT connection.
    client.setServer(MQTT_HOST, MQTT_PORT);
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
    if (WiFi.isConnected() && !client.connected() && sinceReconnect >= 10000)
    {
        Log.trace("Connect to MQTT broker %s:%d. Current client state: %d. Connection attempts: %d",
                  MQTT_HOST, MQTT_PORT, client.state(), ++reconnectionAttempts);
        client.connect(clientId.c_str()); // Try to connect to the MQTT broker
        sinceReconnect = 0;
    }
}

MqttSupportClass MqttSupport = MqttSupportClass();