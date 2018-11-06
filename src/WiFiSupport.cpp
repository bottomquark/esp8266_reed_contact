/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "Config.h"

void WiFiSupportClass::setup()
{
    this->connect();
}

void WiFiSupportClass::loop()
{
    this->connect();
}

void WiFiSupportClass::connect()
{
    if (!WiFi.isConnected() && sinceReconnect >= 10000)
    {
        Log.trace("Connect to WIFI network: %s. Current client state: %d. Connection attempts: %d",
                  WIFI_SSID, WiFi.status(), ++reconnectionAttempts);
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        sinceReconnect = 0;
    }
}

WiFiSupportClass WiFiSupport = WiFiSupportClass();