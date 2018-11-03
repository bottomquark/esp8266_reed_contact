/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "MqttSupport.h"
#include "Config.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void MqttSupportClass::setup()
{
    // Set-Up WiFi connection.
    WiFiSupport.setup();

    Log.debug("Connect to MQTT broker ...");

    // Initialize MQTT connection.
    client.setServer(MQTT_HOST, MQTT_PORT);
    this->connect();
}

void MqttSupportClass::loop()
{
    // Check WIFI connection.
    WiFiSupport.loop();

    if (!client.connected())
    {
        Log.debug("Reconnect to MQTT broker ...");
        this->connect();
    }
}

void MqttSupportClass::connect()
{
    digitalWrite(LED_BUILTIN, LOW); // turn on the LED

    // wait for connection
    String clientId;
    while (!client.connected())
    {
        clientId = "ESP8266Client-" + String(random(0xffff), HEX);
        client.connect(clientId.c_str());
        Log.trace("  MQTT state: %d", client.state());
        delay(200);
    }
    Log.debug("  connected to MQTT on %s:%d with client Id %s", MQTT_HOST, MQTT_PORT, clientId.c_str());

    digitalWrite(LED_BUILTIN, HIGH); // turn off the LED
}

MqttSupportClass MqttSupport = MqttSupportClass();