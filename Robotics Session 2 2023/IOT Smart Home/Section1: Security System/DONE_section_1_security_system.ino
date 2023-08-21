// Created by Phebe Le in Session 2 2023
// This section of the code is for the outside of the IOT smart home
/*
  The outside of the smart home will be a security system that will require a high reading 
  from a force sensor and motion sensor to activate the servo-powered door. 
  If motion is detected a LED will turn on. This door can also be controlled from a web server for accessibility.

  include: stack, queues, pointers, self-defined library
*/

//include libraries
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
#include "pitches.h"

//ethernet
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };  //physical mac address
byte ip[] = { 192, 168, 5, 67 };                      // ip in lan
byte gateway[] = { 192, 168, 1, 1 };                  // internet access via router: communidataion of button
byte subnet[] = { 255, 255, 255, 0 };                 //subnet mask: communidataion of button
EthernetServer server(80);

const int led = 4;  //led for door
int pos = 0;        //position of servo

const int speaker = A1;  //speaker for door

int buttonState = 0;  //state of button
int doorButton = A2;   //button for door

Servo microservo;
String readString;

bool motionDetection = false;

// notes for arduino melody (taken from an example)
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations for arduino melody (taken from an example)
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


// Stack size and pointer for the stack
const int stackSize = 10;
int stack[stackSize];
int* stackPtr = &stack[0];
int* stackTop = &stack[0];

// Queue size and pointer for the queue
const int queueSize = 10;
int queue[queueSize];
int* queuePtr = &queue[0];
int* queueFront = &queue[0];
int* queueRear = &queue[0];

void setup() {
  // Open serial communidataions and wait for port to open:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(doorButton, INPUT);
  microservo.attach(A3);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // Create a client connection
  EthernetClient client = server.available();

  physicalOpen();  // Open the door

  // start ethernet web server
  if (client) {
    while (client.connected()) {
      if (client.available()) {
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
          client.println("<H1>Security Door</H1>");
          client.println("<hr />");
          client.println("<br />");
          client.println("<H2>Door Status:</H2>");
          client.println("<br />");
          client.println("<a href=\"/?button1on\"\">Turn On LED</a>");
          client.println("<a href=\"/?button1off\"\">Turn Off LED</a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href=\"/?button2on\"\">Open door</a>");
          client.println("<a href=\"/?button2off\"\">Close Door</a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<a href=\"/?button3.1\"\">Play music</a>");
          client.println("<a href=\"/?button3.2\"\">Quick Open</a><br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<br />");
          client.println("<p>Created by Phebe Le in Session 2 2023</p>");
          client.println("<br />");
          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);
          client.stop();

          //methods to control buttons
          if (readString.indexOf("?button1on") > 0) {  //button to turn led on
            digitalWrite(led, HIGH);
          }
          if (readString.indexOf("?button1off") > 0) {  //button to turn led on
            digitalWrite(led, LOW);
          }
          if (readString.indexOf("?button2on") > 0) {  //button to open door
            openedDoor();
          }
          if (readString.indexOf("?button2off") > 0) {  //button to close door
            closedDoor();
          }
          if (readString.indexOf("?button3.1") > 0) {  //button to play music
            music();
          }
          if (readString.indexOf("?button3.2") > 0) {  //button for quick open
            quickOpen();
          }
          // clearing string for next read
          readString = "";
        }
      }
    }
  }
}



// function to open door and set motion light on
void openedDoor() {
  Serial.println("Door is open!");
  digitalWrite(led, HIGH);
  microservo.write(90);
}

// function to close door and set motion light off
void closedDoor() {
  Serial.println("Door is closed");
  digitalWrite(led, LOW);
  microservo.write(0);
}

// function to play music
void music() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int* p_speaker = &speaker;
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(*p_speaker, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(*p_speaker);
  }
}

//function to quickly open door and then close it
void quickOpen() {
  int data = analogRead(pos);

  //enter new data entry for queue/stack (or add on next to previous data entry)
  enqueueQueue(data);  
  pushStack(data); 

  //Print stack or queue
  Serial.println("Printing stack:");
  printStack();
  Serial.println("Printing Queue:");
  printQueue();

  //move servo position 90 degress
  for (data = 0; data < 90; data += 3) {
    microservo.write(data);
    delay(20);
  }
  for (data = 0; data < 90; data += 3)  
  {                                  
    microservo.write(data);           
    delay(15);                       
  }
}
void physicalOpen() {
  buttonState = digitalRead(doorButton);
  if (buttonState == HIGH) {
    openedDoor();
    Serial.println("Door has been physically opened");
  }
}
void pushStack(int value) {
  // Check if the stack is not full
  if (stackPtr < stack + stackSize) {
    *stackPtr = value;
    stackPtr++;
  } else {
    // Stack overflow, handle as needed (e.g., pop elements to make space)
  }
}

void enqueueQueue(int value) {
  // Check if the queue is not full
  if (queuePtr < queue + queueSize) {
    *queuePtr = value;
    queuePtr++;
  } else {
    // Queue overflow, handle as needed (e.g., dequeue elements to make space)
  }
}

void printStack() {
  Serial.print("Stack: ");
  int* ptr = stack;
  while (ptr < stackPtr) {
    Serial.print(*ptr);
    Serial.print(" ");
    ptr++;
  }
  Serial.println();
}

void printQueue() {
  Serial.print("Queue: ");
  int* ptr = queueFront;
  while (ptr < queuePtr) {
    Serial.print(*ptr);
    Serial.print(" ");
    ptr++;
  }
  Serial.println();
}