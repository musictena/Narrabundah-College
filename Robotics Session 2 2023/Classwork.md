# Class topics

#### required
-  malloc
-  pointers, dereferencing
-  interrupts
-  classes
-  2d multidimensional array

## Variable recap
- memory address (aka location value is lvalue); used to store location of value for compiler
- stored data (aka register value is rvalue); is used to store the specific data in the memory  
## Multi-dimensional array
![image](https://user-images.githubusercontent.com/109852885/236711491-2141c877-e2ab-45f4-bc40-ca77cba7963b.png)![image](https://user-images.githubusercontent.com/109852885/236711676-c37f2bab-77cd-461e-a6ca-187dd2991575.png)
- does the inner for loop first, once it meets the condition it moves to the outside for loop
#### Two ways to initiate a multi-dimensional array 
```
int a[2][3] = {{1,2,3},{4,5,6}};
OR
int a[2][3] = {1,2,3,4,5,6};

```
## Memory
- memory in systems is considered volatile and non-volatile. Volatile memory is temporary short-term memory. This is data that stores memory whilst the system is running but the data is lost when the system shuts down. 
- nonvolatile memory is permanent memory that is not lost when the system is turned off. 
## SD card module
- The sd card module is used to read data and write data onto an sd card and show it within the Arduino Serial monitor. 
### Programs that it can do
- writing to files on sd card
- read from a file stored on an SD card
## Interrupts
- Interrupt: a section of hardware that monitors an input pin and interrupts a program (known as a interrupt vector) by letting the program know the input pin has changed its state
- a better alternative to polling
###### Polling
- is the method of constantly checking the state of input devices such as a button
- disadvantages: if there are several inputs it becomes slower

### Types of interrupts
- the difference is to allow what conditions you wish to trigger the interrupt for an input
##### Change (a combination of rising and falling)
-  either where it can go from high to low
##### Rising
- a rising edge where a signal goes from low to high
##### Falling
- a signal where the signal goes from high to low

### Interrupt service routine (ISR)
- when conditions (rising, falling, change) are met, the Arduino will run an ISR
- ISR a program that runs uniquely based off the type of interrupt
#### Tips for using interrupts
- the code in ISR should be short because the microcontroller will stop all programs to execute the isr before it continues another program. Usually use it to set a flag or change a state. do not have it execute a full code
- isr cannot return or take parameters
- time-related functions ``delay||millie`` will not work in isr because they are based on interrupt functions
- ``delay microseconds``will work because it's not interrupt based
- any varibale that is changed in isr should be declared with the volatile modifier
- only certain pins will have interrupt capabilities. Arduino digital pins 2 and 3 have interrupt capabilities
- not all chips support all 3 kinds of interrupts, some may only work with change pins, some have all 3 capabilities
- 
### Implementation of interrupt
- Create variable:``volatile int buttonFlag;``: declares int can be changed without the rest of the Arduino body knowing about it
- Initialise interrupt to pin: ``attachInterrupt(digitalPinToInterrupt(2), ISR_button, CHANGE)// attch the digital pin 2 to interrupts, isr_button=the function you wish to run {use ISR_ because it's default}``
- ISR function ``void...{buttonFlag=1;}``
## Malloc (Memory Allocation)
- is an array that allows you to provide memory for an array if the length is already known
### Types of Malloc
#### Static 
- Memory gets allocated to stack
- eg. int a, char b, float c 
#### Dynamic
- Used when the number of stored data during runtime is unknown 
- Memory gets allocated to heap
- Dynamic functions: malloc, calloc is declared in ``stdlib.h`` which is a standard library header file
##### RAM (Random Access Memory)
- Both Stack and heap are stored in RAM
### Implementation
``
int *ptr; //declaration of an integer in the stack
ptr = malloc(5* sizeof(int)); // malloc(5*4[because int is 4]) --> 20 bytes of memory get allocated to the heap
--> malloc returns the base address of the allocated memory which is stored int ptr 
*(ptr+0) = 10; //the value stored at the first value (garbage value --> at memory address 1000)
*(ptr+1) = 20;
*(ptr+1) = 30;
*(ptr+1) = 40;
*(ptr+1) = 50;
 ``
--> When the heap memory is full and cannot be allocated more memory, the malloc statement returns null
##### Tips for using Malloc
--> Use a test case for malloc to check memory allocation
`` if (ptr != NULL){
      Serial.print("Memory created successfully")  
    }else{
      return 0;
    }
## Struct
- A collection of different data types similar to a dict 
- Instead of using a number like array[1], it uses the dot notation

```
struct student{
   String name;
   int age;
   int roll_no;
}
void setup() {
   //Put your setup code here, to run once:
   Serial.begin(9600);
   Serial.println();
   student A = {"Yash", 25, 26};
   Serial.println(A.name);
}
```
## Pointer
- a pointer is a variable that references the memory address of another variable (aka the rvalue is the lvalue of another variable)
- To create declare a pointer; ```int *myPointer```
- ``` px``` is a good habit for naming pointers to point to x

#### Referencing: To get the memory address of a variable, use the address-of operator (&), aka referencing operator. 
- &: a unary operator that returns lvalue of variable
- To assign a pointer to a location; ```myPointer = &myVar```

#### Dereferancing aka indirection: used to obtain/get/change the value of the main variable
- it occurs when there's no data type in front of a variable 
- eg. 
```
int * pX = &x //integer of pointer px is equal to the memory location of variable x --> referencing
int y = *pX;  // integer y is set to the thing set by pointer pX (essentially 2 steps back) -->derefernacing
```
- Indirection operator (*): is used to manipulate the actual value stored at the memory address

### Importance
- The use of static and dynamic memory allocation
#### Pointer Arduino example 
```
int myVar = 10;
int *myPointer;
myPointer = &myVar;

  Serial.print("myVar's lvalue: ");
  Serial.println((long) &myVar, DEC);
  Serial.print("myVar's rvalue: ");
  Serial.println(myVar, DEC);
  Serial.println();
  
  Serial.print("myPointer's lvalue: ");
  Serial.println((long) &myPointer, DEC);
  Serial.print("myPointer's rvalue: ");
  Serial.println((long) myPointer, DEC);
  Serial.println();
  
  OUTPUT:
  
  myVar's lvalue: 2298
  myVar's rvalue: 10
  myPointer's lvalue: 2296
  myPointer's rvalue: 2298
```
#### How it can be used
-  to point to a pin variable
```
int* p_pin = &pin; // create a pointer to the pin variable
digitalWrite(*p_pin, HIGH); // turn the LED on 
```
- to make two arrays go off at the same time
```
int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // the notes of the melody
int duration[] = {200, 200, 200, 200, 200, 200, 200, 200}; // the duration of each note
int melodyLength = size of(melody) / size of(int); // the length of the melody

  for (int i = 0; i < melodyLength; i++) {
    int* p_note = &melody[i]; // create a pointer to the current note
    int* p_duration = &duration[i]; // create a pointer to the current note duration
    
    tone(speakerPin, *p_note, *p_duration); // play the current note
    
```
### Terminology
- Core files: These are pieces of code that are built into the Arduino IDE eg. digitalWrite, digitalRead, delay
- Registers are ... that help to improve the speed and decrease the memory storage place within a microcontroller. More difficult to read. 

## Vector 
- used for temporary memory allocation
- It stores information for a small amount through an array
- this can be done by using the vector library <Vector.h>
- the memory is stored in the cloud until it reaches a certain limit (malloc) then send the data to the desired location.

## 
## Further study

### Links
- https://engineerworkshop.com/blog/pointers-arrays-and-functions-in-arduino-c/: how to use pointers (array[need documentation], functions[confusing])
- https://reefwing.medium.com/pointers-in-c-and-c-for-arduino-911ab1afe82e: confusing
- https://cplusplus.com/doc/tutorial/: list of all terminology
- https://www.youtube.com/watch?v=QyKVbQH4Hi4&list=PLKL6KBeCnI3X7cb1sznYuyScUesOxS-kL: registers with tinkercad
### Terms that I have no clue about + kinda need to know

#### Pointers
- how pointers can be used to make a struc be in the scope of a function
- static and dynamic memory
- memory heap eg. malik or s-break
- memory allocators
- malloc
- socket
- C++ Vector
#### Array
- multi-dimensional arrays

### The rabbit hole of info, that really does not need to be investigated rn
- C++ Lists
- C++ Double-Ended Queues
- Container Adapters
- C++ Stacks
- C++ Queues
- C++ Priority Queues
- Associative Containers
- C++ Bitsets
- C++ Maps
- C++ Multimaps
- C++ Sets
- C++ Multisets
- registers
- segmentation fault
- operator overloading
- socket
- recursion
- foo
- metasyntactic variables
- STL
