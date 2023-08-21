// Created by Phebe Le in Session 2 2023
// This section of the code is for the inside of the IOT smart home
/*
The inside of the smart home will contain three unique sections.  
 - A LED system: LEDs will turn on sequentially depending on the location of object in the smart home.
  Lights can also be controlled by webserver where different buttons would activate the outputs
 - Monitoring system: A LCD screen displays movement action occurring, an sd card would write 
    and be able to read data but there is no more space for the sd library in the sketch
    - the location where the sd card should be is commented out 
 - Voice system: A mic will play music from the peizo speaker
*/

// include libaries

//self-defined libaries
#include <SoundSystem.h>
#include <LightUp.h>

//required libaries
#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD
#include <SPI.h>
// #include <SD.h>  //commented out due to no more space in Arduino sketch
#include <Ethernet.h>

// input and output pins
const int sensorPin = A0;
const int buttonIn = A2;
const int speaker = A1;
const int trigPin = 7;
const int echoPin = 8;

// LEDS
const int numLeds = 6;
const int ledPins[3][3] = { { 2, 3, 4 }, { 5, 6, 9 } };

// SD
// const int chipSelect = 4;

// instances of classes
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
SoundSystem SoundSystem(sensorPin, buttonIn, speaker);
LightUp LightUp(trigPin, echoPin, ledPins, numLeds);

//ethernet
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };  //physical mac address
byte ip[] = { 192, 168, 5, 67 };                      // ip in lan
byte gateway[] = { 192, 168, 1, 1 };                  // internet access via router: communication of button
byte subnet[] = { 255, 255, 255, 0 };                 //subnet mask: communication of button
EthernetServer server(80);
String readString;

void setup() {

  //Setup sound and light function/class
  Serial.begin(9600);
  LightUp.initial();
  SoundSystem.setup();

  //lcd
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("IOT Home");
  lcd.setCursor(2, 1);
  lcd.print("System");

  // //initalise Sd card
  // Serial.print("Initializing SD card");
  // if (!SD.begin(chipSelect)) {
  //   Serial.println("Card error");
  //   return;
  // }
  // Serial.println("card initialized.");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {

  // setup the ethernet
  EthernetClient client = server.available();
  SoundSystem.loop();
  LightUp.ultraSetup();
  ultraImplement();

  //ethernet webpage setup
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        Serial.println("avaliable");
        char c = client.read();
        //to store the characters for buttons
        if (readString.length() < 100) {
          readString += c;
        }
        //if HTTP request has ended
        if (c == '\n') {
          Serial.println(readString);         //print to serial monitor for debuging
          client.println("HTTP/1.1 200 OK");  //send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta charset='UTF-8'>");
          client.println("<meta name='author' content='Phebe Le'>");
          client.println("<meta http-equiv='X-UA-Compatiable' content='IE-edge'>");
          client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='https://randomnerdtutorials.com/ethernetcss.css' />");
          client.println("<TITLE>Security Door</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<H1>IOT Home</H1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<H2>Door Status:</H2>");
          client.println("<br />");
          client.println("<a href=\"/?button1on\"\">Turn On 3rd LED</a>");
          client.println("<a href=\"/?button1off\"\">Turn on 4th LED</a><br />");
          client.println("<p>Created by Phebe Le in Session 2 2023</p>");
          client.println("<br />");
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          client.stop();

          //for the buttons
          if (readString.indexOf("?button1on") > 0) {
            digitalWrite(ledPins[0][2], HIGH);
            delay(20);
          }
          if (readString.indexOf("?button1off") > 0) {
            digitalWrite(ledPins[0][3], HIGH);
            delay(30);
          }
          // clearing string for next read
          readString = "";
        }
      }
    }
  }
}
//function for the detection of ultraonic sensor and movement of lights
void ultraImplement() {
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;  // this number is taken from another website, to ensure accuracy of calculation
  
  // //write to the sd card with the file data.txt
  // File sdcard_file = SD.open("light.txt", FILE_WRITE);
  // if (sdcard_file) {

    // create the mapping of the leds in regards to the ultrasonic sensor
    for (int i = 0; i < numLeds; i++) {
      if (distance >= (i * 10) && distance < ((i + 1) * 10)) {
        for (int j = 0; j <= i; j++) {
          digitalWrite(ledPins[0][j], HIGH);
          for (int k = 0; k < 8; k++) {
            digitalWrite(ledPins[1][k], HIGH);
          }
        }

        for (int j = i + 1; j < numLeds; j++) {
          digitalWrite(ledPins[0][j], LOW);
          for (int k = i + 1; k < 8; k++) {
            digitalWrite(ledPins[1][k], LOW);
          }
        }
      }
    }
    // serial print to debug and check
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(100);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Distance:");
    lcd.setCursor(2, 1);
    lcd.print(distance);
    lcd.print("cm");

  //   //write to SD then display/alert
  //   sdcard_file.println("Distance of Ultrasonic sensor from door: ");
  //   sdcard_file.println(distance);
  //   sdcard_file.close();
  // } else {
  //   Serial.println("error opening light.txt");
  // }
}
