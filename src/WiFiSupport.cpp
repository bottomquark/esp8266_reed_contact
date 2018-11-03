/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "Config.h"

void WiFiSupportClass::setup()
{
    Log.debug("Connect to WIFI network ..." CR);
    this->connect();
}

void WiFiSupportClass::loop()
{
    if (WiFi.status() == WL_DISCONNECTED)
    {
        Log.debug("Reconnect to WIFI network ..." CR);
        this->connect();
    }
}

void WiFiSupportClass::connect()
{
    digitalWrite(LED_BUILTIN, LOW); // turn on the LED

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        Log.trace("WiFi state: %d" CR, WiFi.status());
        delay(200);
    }
    Log.debug("... connected to %s. Got IP address %s" CR, WIFI_SSID, WiFi.localIP().toString().c_str());

    digitalWrite(LED_BUILTIN, HIGH); // turn off the LED
}

WiFiSupportClass WiFiSupport = WiFiSupportClass();