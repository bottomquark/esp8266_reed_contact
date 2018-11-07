/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <Arduino.h>
#include <ArduinoLog.h>
#include <ArduinoJson.h>
#include <elapsedMillis.h>
#include "MqttSupport.h"

#define REED_PIN D1

elapsedMillis sinceLastTransmission;

/**
 * Helper method to print timestamp to Log output.
 */
void printTimestamp(Print *_logOutput)
{
  char c[12];
  sprintf(c, "%10lu ", millis());
  _logOutput->print(c);
}

/**
 * Helper method to print carriage return to Log output.
 */
void printNewline(Print *_logOutput)
{
  _logOutput->print(CR);
}

/**
 * Read the Reed Contact pin.
 * @return true, if reed contact closed, otherwise false.
 */
bool isReedClosed()
{
  // for normally open contacts. Invert for normally closed ones (reedValue == 1)
  return digitalRead(REED_PIN) == 0;
}

/**
 * 'setup()' gets called once when the microcontroller gets powered on or reset.
 */
void setup()
{
  // Initialize logger.
  Log.init(LOG_LEVEL_VERBOSE, 115200);
  Log.setPrefix(printTimestamp);
  Log.setSuffix(printNewline);
  Log.trace("--- start set-up ---");

  // Initialize MQTT connection.
  MqttSupport.setup();

  // Configure REED_PIN as input and the built in LED as output
  pinMode(REED_PIN, INPUT);     // REED_PIN is pin D1
  pinMode(LED_BUILTIN, OUTPUT); // LED_BUILTIN is also pin D4
}

/**
 * Endless loop, gets executed automatically as fast as possible.
 */
void loop()
{
  // Check MQTT connection.
  MqttSupport.loop();

  if (isReedClosed())
  {
    //set the pin low (turn on the LED, functionality is inverted here)
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);

    // Allocate JsonBuffer. Use http://arduinojson.org/assistant to compute the capacity.
    StaticJsonBuffer<100> jsonBuffer;

    // Create the root object
    JsonObject &root = jsonBuffer.createObject();
    root.set("measure", 1);
    root.set("duration", millis());

    //
    String output;
    root.printTo(output);
    bool r = MqttSupport.publish(output.c_str());

    Log.debug("Message sent %s, Sent result: %T, Connection state: %T", output.c_str(), r, MqttSupport.isConnected());
  }

  digitalWrite(LED_BUILTIN, HIGH);
}
