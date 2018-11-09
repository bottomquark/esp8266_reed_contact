/*
 * MIT License <http://opensource.org/licenses/MIT>.
 */

#include <Arduino.h>
#include <ArduinoJson.h>
#include <QueueList.h>
#include <elapsedMillis.h>
#include "Global.h"
#include "MqttSupport.h"

#define REED_PIN D1

#define REED_PIN_STATE_OPEN 1
#define REED_PIN_STATE_CLOSED 0

// Define elapsed time since last data transmission.
elapsedMillis sinceLastTransmission;

// Define a queue for reed contact measurements.
QueueList<String> reedMeasurements;

// Contaons last state of reed pin.( Default is open = 1)
int reedPinLastState = REED_PIN_STATE_OPEN;

/**
 * Reads the reed contact pin and identifies whether the reed state switches to close.
 * @return true, if reed contact switches to close state, otherwise false.
 */
bool isReedSwitchedToClose()
{
  int reedPinState = digitalRead(REED_PIN);
  bool result = (reedPinState != reedPinLastState) && (reedPinState == REED_PIN_STATE_CLOSED);
  reedPinLastState = reedPinState;
  return result;
}

/**
 * Created a JsonObject containing mreed contact measurement and current millis.
 * @param reed measurement
 * @return JsonObject converted to String.
 */
String createReedMeasurement(int value)
{
  // Allocate JsonBuffer. Use http://arduinojson.org/assistant to compute the capacity.
  StaticJsonBuffer<100> jsonBuffer;

  // Create the root object
  JsonObject &reedMeasurement = jsonBuffer.createObject();
  reedMeasurement.set("measure", value);
  reedMeasurement.set("duration", millis());

  // Write generated JsonObject to String.
  String result;
  reedMeasurement.printTo(result);

  return result;
}

/**
 * Checks the reed pinn and if closed, write the measurement into the local queue.
 */
void collectReedMessages()
{
  if (isReedSwitchedToClose())
  {
    // Set the pin low (turn on the LED, functionality is inverted here)
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);

    // Buffer the messages in the queue.
    String reedMeasurement = createReedMeasurement(1);
    reedMeasurements.push(reedMeasurement);
  }
  digitalWrite(LED_BUILTIN, HIGH); // Turn LED off.
}

/**
 * Sends the reed messages containing in the local queue to MQTT broker.
 */
void sendReedMessages()
{
  if (!reedMeasurements.isEmpty() && MqttSupport.isConnected())
  {
    String reedMeasurement = reedMeasurements.peek();                     // Get the message from the loca queue.
    bool sentSuccessfully = MqttSupport.publish(reedMeasurement.c_str()); // try to send the message
    if (sentSuccessfully)
    { // if sent successfully => remove from local queue.
      reedMeasurements.pop();
    }
    Log.debug("Message %s was sent %s.", reedMeasurement.c_str(), (sentSuccessfully ? "successfully" : "not successfully"));
  }
}

/**
 * 'setup()' gets called once when the microcontroller gets powered on or reset.
 */
void setup()
{
  // Initialize logger.
  setupLogger();

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
  MqttSupport.loop();    // Check MQTT connection.
  collectReedMessages(); // Collect reed messages in the local queue.
  sendReedMessages();    // Send messages from local queue to MQTT.
}
