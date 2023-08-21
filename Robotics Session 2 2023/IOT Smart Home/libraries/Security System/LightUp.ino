
#include "LightUp.h"

// Initialization of main variables
const int trigPin = 7;
const int echoPin = 8;
const int numLeds = 6;
const int ledPins[3][3] = {{2, 3, 4}, {5, 6, 9}};  // Modify this according to your LED pin setup

LightUp LightUp(trigPin, echoPin, ledPins, numLeds);

void setup() {
  Serial.begin(9600);
  LightUp.initial();
}

void loop() {
  LightUp.full();
}