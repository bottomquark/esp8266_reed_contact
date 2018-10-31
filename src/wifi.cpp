#include <wifi.h>
#include <config.h>

void wifiSetup()
{
    Serial.println();
    Serial.print("Connect to WIFI network ...");
    connectToWifiNetwork();
}

void wifiLoop()
{
    if (WiFi.status() == WL_DISCONNECTED)
    {
        Serial.println();
        Serial.print("Reconnect to WIFI network ...");
        connectToWifiNetwork();
    }
}

void connectToWifiNetwork()
{
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    // wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED_BUILTIN, HIGH);

        delay(200);
        Serial.print(".");
        Serial.print(WiFi.status());

        digitalWrite(LED_BUILTIN, LOW);
    }

    Serial.println();
    Serial.print("Connected to ");
    Serial.print(WIFI_SSID);
    Serial.print(". Got IP address: ");
    Serial.print(WiFi.localIP());
}