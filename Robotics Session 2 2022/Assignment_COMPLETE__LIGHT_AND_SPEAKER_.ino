#include <LiquidCrystal.h>
#define LCD_LIGHT_PIN A4
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
/* LCD RS pin to digital pin 12
  LCD Enable pin to digital pin 11
  LCD D4 pin to digital pin 5
  LCD D5 pin to digital pin 4
  LCD D6 pin to digital pin 3
  LCD D7 pin to digital pin 2
  LCD Anode Pin to Analog Pin A4
  Push Button to digital Pin 8 */
const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int buzzer =  9;       // the number of the buzzer pin

// variables that will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {

  // Setup the number of columns and rows that are available on the LCD.
  lcd.begin(16, 2);
  lcd.noDisplay();

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  //intializes the buzzer pin as an output;
  pinMode (buzzer, OUTPUT);

  // Set the LCD display backlight pin as an output.
  pinMode(LCD_LIGHT_PIN, OUTPUT);

  // Turn off the LCD backlight.
  digitalWrite(LCD_LIGHT_PIN, LOW);
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {

    // Print some text to the LCD.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("what's happening");
    // Turn the backlight on.
    digitalWrite(LCD_LIGHT_PIN, HIGH);
    // Display the text on the LCD.
    lcd.display();

    
    for (int x = 0; x < 3; x++) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      //buzzer sound
      tone(buzzer, 1000); //1KHz sound signal
      delay(500);
      noTone(buzzer);
      delay(1000);    
      }
      delay(1000);
      lcd.clear();
      lcd.setCursor (0, 0);
      lcd.print ("boom!just joking");

      delay(1000);
      lcd.noDisplay();
      digitalWrite(LCD_LIGHT_PIN, LOW);
      
  }
  if (buttonState == LOW) {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    //no sound buzzer
    noTone (buzzer);
    // turn LCD screen off;
    lcd.noDisplay();
  }
} 
