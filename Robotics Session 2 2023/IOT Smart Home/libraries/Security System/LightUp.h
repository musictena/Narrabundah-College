#ifndef LightUp_h
#define LightUp_h
// define the new library and include the arduino library
#include <Arduino.h>

//create a class for the lighting up of the LEDs in sequential order
class LightUp {
public:
  LightUp(int trigPin, int echoPin, int ledPins[][3], int numLeds);
  void initial();
  void full();
  void ultraSetup();
private:
  int _trigPin;
  int _echoPin;
  int _ledPins[3][3];
  int _numLeds;

  
  void ultraImplement();
};

#endif