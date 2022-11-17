//include the library for Arduino and header file
#include <Arduino.h>
#include "ledClass.h"

const int buzzer = 9;
ledClass redLED(5);
ledClass yellowLED(6);
ledClass greenLED(11);

//pin 8 = red, pin 9 = yellow, pin 10 =green
int ledArray[] = {10, 9, 8};
int pinCount = 3;
int timer = 100;


void setup() {

  //initialise variables
  for (int i = 0; i < pinCount; i++) {
    pinMode(ledArray[i], OUTPUT);
  }
  pinMode (buzzer, OUTPUT); //buzzer
  pinMode (5), OUTPUT; //button
}
void loop() {
  button = digitalWrite(5);
  if (button == HIGH) {
    tone(buzzer, 1000);
    greenLED.ledFunction(timer);
    greenLED.onFunction();
    yellowLED.ledFunction(timer);
    yellowLED.onFunction();
    redLED.ledFunction(timer);
    redLED.onFunction();
    noTone(buzzer);
    greenLED.offFunction();
    yellowLED.offFunction();
    redLED.offFunction();
  } else {
    for (int i = 0; i < pinCount; i++) {
      digitalWrite(ledArray[i], HIGH);
      delay(timer);
      digitalWrite(ledArray[i], LOW);
    }


  }










}

void music() {



}
