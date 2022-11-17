//created by Phebe Le in 2022
#include <Servo.h>                    //add Servo library
#include <LiquidCrystal.h>            //add LCD library
#include <pitches.h>                  //add Pitch library

#define melodyPin 9                   //speaker on Pin 9

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //define lcd pins
Servo myservo;                        //create variable name for servo


// this melody code was found in Arduino Project Hub v

//create array for 'melody' which will be for Song 3 (Jingle Bells)
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

//create a tempo array for 'melody'
int tempo[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

// create array for 'wish_melody' which will be for Song 2 (We wish you a Merry Christmas)

int wish_melody[] = {
  NOTE_B3,
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

//create a tempo array for 'wish_melody'
int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

// create array for 'santa_melody' which will be for Song 1 (Santa Claus is coming to town)

int santa_melody[] = {
  NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
  NOTE_D4, NOTE_F4, NOTE_B3,
  NOTE_C4
};

//create a tempo array for 'santa_tempo'
 
int santa_tempo[] = {
  8,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 4, 4,
  8, 8, 4, 2,
  4, 4, 4, 4,
  4, 2, 4,
  1
};

// This code was found within Arduino Project Hub ^



const int Pin = 6; // define servo pin on pin 6

int switchOne = 0;      //button v
int switchTwo = 0;
int switchThree = 0;    //button ^

int ledPins[] = {A1, A2, A3, A4, A5}; // the pin that the LED is attached to
int pinCount = 5;
int sensor = A0;              // the pin that the sensor is attached to
int state = LOW;             // by default, no motion detected
int val = 0;                  // variable to store the sensor status
int pos = 0;    // variable to store the servo position
int k1;
char Text;

String Split;
String angle;


void setup() {
  Serial.begin(9600);        // initialize serial monitor
 
  myservo.attach(Pin);      // attach the servo to the const int pin
 
  pinMode(9, OUTPUT); // Buzzer
  pinMode(13, OUTPUT); // Led indicator when singing a note
  pinMode(7, INPUT); //define button 1 on pin 7, as an input
  pinMode(8, INPUT); //define button 2 on pin 8, as an input
  pinMode(10, INPUT); // define button 3 on pin 10, as an input
  pinMode(sensor, INPUT);    // initialize sensor as an input
 
  lcd.begin(16, 2); //lcd start code
  lcd.setCursor(0, 0); //lcd set cursor
  lcd.print("Welcome, press");
  lcd.setCursor(0, 1);
  lcd.print("any button");
 
 
 
  for (int thisPin = 0; thisPin < pinCount; thisPin++)
  {
   
    pinMode(ledPins[thisPin], OUTPUT);
  }
  pinMode (Pin, OUTPUT);
 
}

void loop() {
 
  switchOne = digitalRead(7);// read the value of button pin 1
  switchTwo = digitalRead(8); // read the value of button pin 2
  switchThree = digitalRead(10); //read the value of button pin 3
 
  if (switchOne == HIGH) {    //if button 1 is pressed
    sing(1);    //play on buzzer, array 'melody_santa' with 'santa_tempo'
  }
  else if (switchTwo == HIGH) {   //if button 2 is pressed
    sing(2);// play on buzzer, array 'wish_melody' with 'with_tempo'
  } else if (switchThree == HIGH) {   //if button 3 is pressed
    sing(3);    //play on buzzer, array 'melody' with 'tempo'
  }
 
   val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {      // check if the sensor is HIGH
      for (int thisPin = 0; thisPin <= 5; thisPin++)
        {
          digitalWrite(ledPins[thisPin], HIGH);// turn LED ON
          delay(200);// delay 200 milliseconds
        }
  if (state == LOW) {
      Serial.println("Motion detected!");
      state = HIGH;       // update variable state to HIGH
    }
 
  else {
        for (int thisPin = 5; thisPin >= 0; thisPin--)
          {
            digitalWrite(ledPins[thisPin], LOW);
            delay(200);
          }
   
      if (state == HIGH){
        Serial.println("Motion stopped!"); //print on lcd screen that 'motion stopped'
        state = LOW;       // update variable state to LOW
    }
  }
  }
 
  //below is the code that is recommended for the app
   if(Serial.available())

  {

    Text = Serial.read();

    Split = Split + Text;


    if (Text == '*') {
   
          Serial.println(Split);
   
          Split = Split.substring(0, Split.length() - 1); // Minus one character to get previous positon
   
          k1 = Split.indexOf('*');//find the position of *
   
          angle = Split.substring(0, k1); //define angle as the starting psoiton 0 and k1
   
          myservo.write(angle.toInt());   //write the angle as an integer and makes sero move to that angle
   
          delay(15);                    //take 0.015 secs to get there
   
     
   
          Split = "";
   
      }

    }
  //end of code from servo app
 
}

int song = 0;

void sing(int s) {
 
  song = s;
 
  // if song 3 is chosen display the words 'we wish you a merry christmas'
  if (song == 3) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("We wish you a ");
    lcd.setCursor(0, 1);
    lcd.print("Merry Christmas");
    int size = sizeof(wish_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      int noteDuration = 1000 / wish_tempo[thisNote];//calculate the frequency/pitch of the wish_tempo
      buzz(melodyPin, wish_melody[thisNote], noteDuration); //using the piezo speaker, play the given song with the given duration of the note
     
      int pauseBetweenNotes = noteDuration * 1.30;  //define the pause between notes (30)
      delay(pauseBetweenNotes);//call the delay as a variable

     
      buzz(melodyPin, 0, noteDuration); // stop the tone playing:
     

    }
 
  // if song 2 is chosen display the words 'Santa Claus is coming to town'

  } else if (song == 2) {
       lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Santa Claus is ");
    lcd.setCursor(0, 1);
    lcd.print("coming to town");
    int size = sizeof(santa_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      int noteDuration = 900 / santa_tempo[thisNote];
      buzz(melodyPin, santa_melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

     
      buzz(melodyPin, 0, noteDuration);
     

    }
   
  // if song 1 is chosen display the words 'Jingle Bells'

  } else if (song == 1) {
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Jingle Bells");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(melodyPin, 0, noteDuration);

    }
  }
 
}

//
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions

  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin as high
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin as low
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);  //turn led indicator off

}
