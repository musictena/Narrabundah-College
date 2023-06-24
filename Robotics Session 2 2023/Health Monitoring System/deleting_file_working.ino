// Examplar code from Arduino Examples. Editing has been completed. 
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }

  //initialisation of SD card
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  if (SD.exists("data.txt")) {
    Serial.println("data.txt exists.");
  } else {
    Serial.println("data.txt doesn't exist.");
  }


  // Check to see if the file exists:
  if (SD.exists("data.txt")) {
    Serial.println("data.txt exists.");
  } else {
    Serial.println("data.txt doesn't exist.");
  }

  // delete the file:
  Serial.println("Removing data.txt...");
  SD.remove("data.txt");

  if (SD.exists("data.txt")) {
    Serial.println("data.txt exists.");
  } else {
    Serial.println("data.txt doesn't exist.");
  }
}

void loop() {
}
