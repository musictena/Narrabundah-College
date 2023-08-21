#include "SoundSystem.h"

const int sensorPin = A0;
const int buttonIn = 11;
const int speaker = 8;

SoundSystem SoundSystem(sensorPin, buttonIn, speaker);

void setup() {
  SoundSystem.setup();
}

void loop() {
  SoundSystem.loop();
}
