#include <Servo.h>

// Stack size and pointer for the stack
const int stackSize = 10;
int stack[stackSize];
int stackIndex = 0;

// Queue size and pointer for the queue
const int queueSize = 10;
int queue[queueSize];
int queueFront = 0;
int queueRear = 0;

Servo microservo;
bool motionDetection = false;
int pos = 0;

void setup() {
  Serial.begin(9600);
  microservo.attach(13);
}

void loop() {
  for (int x = 0; x < 4; x++) {
    quickOpen();
  }
}

void pushStack(int value) {
  // Check if the stack is not full
  if (stackIndex < stackSize) {
    stack[stackIndex] = value;
    stackIndex++;
  } else {
    // Stack overflow!
  }
}
void enqueueQueue(int value) {
  // Check if the queue is not full
  if ((queueRear + 1) % queueSize != queueFront) {
    queue[queueRear] = value;
    queueRear = (queueRear + 1) % queueSize;
  } else {
    // Queue overflow!
  }
}
void printStack() {
  Serial.print("Stack: ");
  for (int i = 0; i < stackIndex; i++) {
    Serial.print(stack[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void printQueue() {
  Serial.print("Queue: ");
  int currentIndex = queueFront;
  while (currentIndex != queueRear) {
    currentIndex = (currentIndex + 1) % queueSize;
    Serial.print(queue[currentIndex]);
    Serial.println(" ");
  }
  Serial.println();
}

void quickOpen() {
  int cat = analogRead(pos);

  enqueueQueue(cat);
  pushStack(cat);
  Serial.println("Printing stack:");
  printStack();
  Serial.println("Printing Queue:");
  printQueue();
  for (cat = 0; cat < 90; cat += 3) {
    microservo.write(cat);
    delay(20);
  }
  for (cat = 0; cat < 90; cat += 3)  
  {                                  
    microservo.write(cat);         
    delay(15);                    
  }
}
