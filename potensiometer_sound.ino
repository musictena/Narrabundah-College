
int LED1 = 3;
int LED8 =  10;
int buzz = 11;
int in_p = A0;

void setup() {
  for(int i= LED1; i <= LED8; i++)
    pinMode(i, OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(in_p, INPUT);
}

void loop() {

  int val = analogRead(in_p);
  int lastLed = map(val, 0, 1023, LED1, LED8);

  for(int i = LED1; i <= lastLed; i+=1)
  {
    digitalWrite(i, HIGH);
    delay(2);
    digitalWrite(i, LOW);
    tone(buzz,val*3,10);
  }

}
