//include header file
#include "LightUp.h"

//initialise all the required inputs and outputs
LightUp::LightUp(int trigPin, int echoPin, int ledPins[][3], int numLeds) {
  _trigPin = trigPin;
  _echoPin = echoPin;
  _numLeds = numLeds;


  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      _ledPins[i][j] = ledPins[i][j];
    }
  }
}

//initise the input and output pins from the class
void LightUp::initial() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);

  for (int i = 0; i < _numLeds; i++) {
    pinMode(_ledPins[0][i], OUTPUT);
    pinMode(_ledPins[1][i], OUTPUT);
  }
}

// setup the ultrasonic sensor method
void LightUp::ultraSetup() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
}

//make the leds light up through the ultrasonic sensor method
void LightUp::ultraImplement() {
  int duration = pulseIn(_echoPin, HIGH);
  int distance = duration * 0.034 / 2; // this number is taken from enother website, to ensure accuracy of calculation
    //increase led
  for (int i = 0; i < _numLeds; i++) {
    if (distance >= (i * 10) && distance < ((i + 1) * 10)) {
      for (int j = 0; j <= i; j++) {
        digitalWrite(_ledPins[0][j], HIGH);
        for (int k = 0; k < 3; k++) {
          digitalWrite(_ledPins[1][k], HIGH);
        }
      }
      //decrease led
      for (int j = i + 1; j < _numLeds; j++) {
        digitalWrite(_ledPins[0][j], LOW);
        for (int k = i + 1; k < 3; k++) {
          digitalWrite(_ledPins[1][k], LOW);
        }
      }
    }
  }
//print the distance in serial
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(100);
}

// combine all the methods together
void LightUp::full() {
  ultraSetup();
  ultraImplement();
}
