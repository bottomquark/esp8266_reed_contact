/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <ArduinoLog.h>
#include "WiFiSupport.h"
#include "Config.h"

void WiFiSupportClass::setup()
{
    sinceReconnect = 10000;
    this->connect();
}

void WiFiSupportClass::loop()
{
    this->connect();
}

void WiFiSupportClass::connect()
{
    if (!this->isConnected() && sinceReconnect >= 10000)
    {
        Log.trace("Connect to WIFI network: %s. Current client state: %d. Connection attempts: %d",
                  WIFI_SSID, WiFi.status(), ++reconnectionAttempts);
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        sinceReconnect = 0;
    }
}

bool WiFiSupportClass::isConnected()
{
    return WiFi.isConnected();
}

WiFiSupportClass WiFiSupport = WiFiSupportClass();