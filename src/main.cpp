/*
 * 
 *
 */
#include <Arduino.h>
#include <wifi.h>

#define REED_PIN D1

//setup() gets called once when the microcontroller gets powered on or reset
void setup()
{
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  Serial.println('\n');

  //configure REED_PIN as input and the built in LED as output
  //LED_BUILTIN is also pin D4
  pinMode(REED_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Set-Up WiFi connection.
  wifiSetup();
}

//endless loop, gets executed automatically as fast as possible
void loop()
{
  // Check WiFi connection.
  wifiLoop();

  uint8_t reedValue = digitalRead(REED_PIN);
  //for normally open contacts. Invert for normally closed ones (reedValue == 1)
  if (reedValue == 0)
  {
    //set the pin low (turn on the LED, functionality is inverted here)
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}
