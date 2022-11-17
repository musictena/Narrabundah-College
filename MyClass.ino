#include <Arduino.h>
#include <MyClass.h>
MyClass redLED(11);
MyClass yellowLED(12);
MyClass greenLED(13);
void setup() {
}
void loop() {

  greenLED.myFunction(2000);
  yellowLED.myFunction(1000);
  redLED.myFunction(1000);
}
