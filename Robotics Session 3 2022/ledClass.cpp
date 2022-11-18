#include <Arduino.h>
#include "ledClass.h"
ledClass::ledClass(int pin) {


  pinMode(pin, OUTPUT);
  _pin = pin;
}
void ledClass::ledFunction(int blinkRate){

digitalWrite(_pin, HIGH);
delay(blinkRate);
digitalWrite(_pin, LOW);
delay(blinkRate);
}
void ledClass::onFunction(){
digitalWrite(_pin, HIGH);

}
void ledClass::offFunction(){
digitalWrite(_pin, LOW);
}
