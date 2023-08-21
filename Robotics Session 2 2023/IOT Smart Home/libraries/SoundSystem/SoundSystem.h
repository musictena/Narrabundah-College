#ifndef SoundSystem_h
#define SoundSystem_h

#include "Arduino.h"

class SoundSystem {
public:
  SoundSystem(int sensorPin, int buttonIn, int speaker);
  void setup();
  void loop();

private:
  int _sensorPin;
  int _buttonIn;
  int _speaker;
  int _buttonState;
  int _melody[8];
  int _noteDurations[8];   
  
  void music();
};
#endif
