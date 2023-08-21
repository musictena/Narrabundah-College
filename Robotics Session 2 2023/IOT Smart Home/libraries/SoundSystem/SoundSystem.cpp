#include "SoundSystem.h"
#include "pitches.h"

SoundSystem::SoundSystem(int sensorPin, int buttonIn, int speaker) {
  _sensorPin = sensorPin;
  _buttonIn = buttonIn;
  _speaker = speaker;
  _buttonState = 0;

  // music array
   int song[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
   int noteTime[] = { 4, 8, 8, 4, 4, 4, 4, 4 };

  for (int i = 0; i < 8; i++) {
    _melody[i] = song[i];
    _noteDurations[i] = noteTime[i];
  }
}

void SoundSystem::setup() {
  pinMode(_sensorPin, INPUT);
  pinMode(_buttonIn, INPUT);
  Serial.begin(9600);
}
 
void SoundSystem::loop() {
  int sensorValue = analogRead(_sensorPin);
  _buttonState = digitalRead(_buttonIn);

  if (_buttonState == HIGH) {
    Serial.println("both are high");
    Serial.print("The value of the mic is:");
    Serial.println(sensorValue);
    music();
  }else{noTone(_speaker);}
}

void SoundSystem::music() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / _noteDurations[thisNote];
    tone(_speaker, _melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(_speaker);
  }
}
