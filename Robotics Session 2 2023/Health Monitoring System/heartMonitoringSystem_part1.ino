/*Created by Phebe Le | Session 2 | Heart Monitoring System  Part 1
 * 
 * This project is replicating a heart-rate watch system that uses output: LEDs, 
 * a buzzer, LCD display screen. Inputs: Pulse-Sensor, Ethernet webserver. It also includes an SD
 * card module which reads and writes data.
 * 
 * Due to the lack of space in the Arduino, the system is split up into two different modules 
 * a stationary system and mobile system. 
 * 
 * This section is Part 1: The mobile systems consists of all outputs, sensor and SD module
 */

#define USE_ARDUINO_INTERRUPTS true  //for consistent pulse sensor entries
//define libraries
#include <Vector.h>
#include <SD.h>
#include <SPI.h>
#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C.h>
#include "myClass.h"

//align libraries to inputs/outputs
LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseSensorPlayground heartMonitor;

int speaker = 9;
int Threshold = 547;
int Instructions_view = 500;  //for waiting time to display instructions on LCD.

const int PulseWire = 0;
const int chipSelect = 4;
const int BUFFER = 20;  //to dynamically store data up till 20 data entries
typedef Vector<int> bpmBuffer;

MyClass redLED(5);
MyClass greenLED(6);

//MyClass
MyClass::MyClass(int pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}
void MyClass::on() {
  digitalWrite(_pin, HIGH);
}
void MyClass::off() {
  digitalWrite(_pin, LOW);
}
void MyClass::blink(int blinking) {
  digitalWrite(_pin, HIGH);
  delay(blinking);
  digitalWrite(_pin, LOW);
  delay(blinking);
}

//This section was copied froman external website to create the the heart displayed on the LCD screen
byte heart1[8] = { B11111, B11111, B11111, B11111, B01111, B00111, B00011, B00001 };
byte heart2[8] = { B00011, B00001, B00000, B00000, B00000, B00000, B00000, B00000 };
byte heart3[8] = { B00011, B00111, B01111, B11111, B11111, B11111, B11111, B01111 };
byte heart4[8] = { B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11111 };
byte heart5[8] = { B00011, B00111, B01111, B11111, B11111, B11111, B11111, B11111 };
byte heart6[8] = { B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11110 };
byte heart7[8] = { B11000, B10000, B00000, B00000, B00000, B00000, B00000, B00000 };
byte heart8[8] = { B11111, B11111, B11111, B11111, B11110, B11100, B11000, B10000 };
//External section ends

void setup() {
  Serial.begin(9600);
  pinMode(speaker, OUTPUT);

  //initalise Sd card
  Serial.print("Initializing SD card");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card error");
    return;
  }
  Serial.println("card initialized.");

  //set up LCD
  lcd.init();
  lcd.backlight();
  pulsing();
  delay(2000);
  lcd.clear();
}

//first intialisation of the LCD
int pulsing() {
  //This section was copied froman external website to create the the heart displayed on the LCD screen
  lcd.createChar(1, heart1);
  lcd.createChar(2, heart2);
  lcd.createChar(3, heart3);
  lcd.createChar(4, heart4);
  lcd.createChar(5, heart5);
  lcd.createChar(6, heart6);
  lcd.createChar(7, heart7);
  lcd.createChar(8, heart8);
  //External section ends

  lcd.setCursor(0, 0);
  lcd.print(" Heart Monitor ");
  lcd.setCursor(0, 1);
  lcd.print("    System     ");
  heartMonitor.analogInput(PulseWire);
  heartMonitor.setThreshold(Threshold);

  if (heartMonitor.begin()) {
    Serial.println("We created a heartMonitor Object !");  //initialisation
  }
}
//second initialisation for LCD
int initial(int a) {
  if (a < 500) {
    a++;
  } else if (a > 499) {
    lcd.setCursor(0, 0);
    lcd.print("Put your finger ");
    lcd.setCursor(0, 1);
    lcd.print("on the sensor   ");
    delay(1000);
    lcd.clear();
    delay(500);
  }
}
//display of BPM on LCD
int LCDHeartView(int bpm) {
  lcd.setCursor(1, 1);
  lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  lcd.setCursor(0, 0);
  lcd.write(byte(3));
  lcd.setCursor(1, 0);
  lcd.write(byte(4));
  lcd.setCursor(2, 0);
  lcd.write(byte(5));
  lcd.setCursor(3, 0);
  lcd.write(byte(6));
  lcd.setCursor(3, 1);
  lcd.write(byte(7));
  lcd.setCursor(2, 1);
  lcd.write(byte(8));
  lcd.setCursor(5, 0);
  lcd.print("Heart Rate");
  lcd.setCursor(5, 1);
  lcd.print(": ");
  lcd.print(bpm);
  lcd.print(" ");
  lcd.print("BPM     ");
}

//alert system for when BPM exceeds the recommended limit
int alertSystem(int bpm) {
  if (bpm > 100 || bpm < 55) {
    int* p_speaker = &speaker;  // create a pointer for the pin variable
    greenLED.off();
    redLED.blink(500);

    tone(*p_speaker, 262);

    delay(200);
    noTone(*p_speaker);
    delay(200);
  } else {
    greenLED.on();
  }
}
void loop() {
  int myBPM = heartMonitor.getBeatsPerMinute(); //define BPM values in a variable
  initial(Instructions_view);

  byte memory[myBPM] = {}; 
    //byte is used to reduce memory leakage (eg. through float)
    //array named memory that takes the parameter myBPM is added
  bpmBuffer vector; //allocate bpmBuffer to the vector

  /*if BPM is detected check for avaliability to dynamicaly allocate memory
  write to SD card, then diaply/alert user if BPM is outside normal range*/
  if (heartMonitor.sawStartOfBeat()) { 
    if (vector.size() <= BUFFER) {
      int* dynamicBuffer = (int*)malloc(BUFFER * sizeof(int));
      if (dynamicBuffer == nullptr) {
        Serial.println("Error allocating memory");
        return;
      }
      for (int i = 0; i < BUFFER; i++) {
        dynamicBuffer[i] = memory[i];
      }
      //write to the sd card with the file data.txt
      File sdcard_file = SD.open("data.txt", FILE_WRITE);
      if (sdcard_file) {
        for (int i = 0; i < BUFFER; i++) {
          //create restrictions for BPM in memory[i]
          if (memory[i] >= 130) {
            memory[i] = memory[i] - 80;
          } else if (memory[i] <= 50 && memory[i] >= 40) {
            memory[i] = memory[i] * 2;
          } else if (memory[i] <= 39) {
            memory[i] = memory[i] + 70;
          }    
          //write to SD then display/alert      
          sdcard_file.println("BPM: ");
          sdcard_file.println(memory[i]);
          Serial.println("♥  A HeartBeat Happened ! ");
          Serial.println("BPM: ");
          Serial.println(memory[i]);
          delay(1000);
          Serial.println("sucess opening data.txt");
          delay(30);
          LCDHeartView(memory[i]);
          delay(30);
          alertSystem(memory[i]);
        }
        sdcard_file.close();
        Serial.println("closed");
      } else {
        Serial.println("error opening data.txt");
      }
      delay(1000);
      Instructions_view = 0;
      delay(20);
      free(memory); //free the memory to reset and continue
    }
    delay(20);
  }
}
