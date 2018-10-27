/*
 * 
 *
 */
#include <Arduino.h>

#define REED_PIN D1

//setup() gets called once when the microcontroller gets powered on or reset
void setup() 
{
  //configure REED_PIN as input and the built in LED as output
  //LED_BUILTIN is also pin D4
  pinMode(REED_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

//endless loop, gets executed automatically as fast as possible
void loop()
{
  uint8_t reedValue = digitalRead(REED_PIN);
  //for normally open contacts. Invert for normally closed ones (reedValue == 1)
  if(reedValue == 0)
  {
    //set the pin low (turn on the LED, functionality is inverted here)
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}
