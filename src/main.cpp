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

  //set the pin high
  digitalWrite(LED_BUILTIN, HIGH);
  //let the microcontroller sleep 100 ms
  delay(100);
  //set the pin low
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);

}
