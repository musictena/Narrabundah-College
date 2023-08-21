#include <Servo.h>

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
