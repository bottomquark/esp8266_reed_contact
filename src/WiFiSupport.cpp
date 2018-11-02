/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "Config.h"

void WiFiSupportClass::wifiSetup()
{
    Log.debug("Connect to WIFI network ..." CR);
    this->connectToWifiNetwork();
}

void WiFiSupportClass::wifiLoop()
{
    if (WiFi.status() == WL_DISCONNECTED)
    {
        Log.debug("Reconnect to WIFI network ..." CR);
        this->connectToWifiNetwork();
    }
}

void WiFiSupportClass::connectToWifiNetwork()
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        Log.trace("WiFi state: %d" CR, WiFi.status());
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
    }

    Log.debug("Connected to %s. Got IP address %s" CR, WIFI_SSID, WiFi.localIP().toString().c_str());
}

WiFiSupportClass WiFiSupport = WiFiSupportClass();