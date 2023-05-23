# Class topics



## Variable recap
- memory address (aka location value is lvalue); used to store location of value for compiler
- stored data (aka register value is rvalue); is used to store the specific data in the memory  
## Multi-dimensional array
![image](https://user-images.githubusercontent.com/109852885/236711491-2141c877-e2ab-45f4-bc40-ca77cba7963b.png)![image](https://user-images.githubusercontent.com/109852885/236711676-c37f2bab-77cd-461e-a6ca-187dd2991575.png)
- does the inner for loop first, once it meets condition it moves to the outside for loop
#### Two ways to initiate a multi-dimensional array 
```
int a[2][3] = {{1,2,3},{4,5,6}};
OR
int a[2][3] = {1,2,3,4,5,6};

```
## Malloc
- Memory Allocation
- is a array that allows you to provide memory for an array if the lengh already known
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
   // put your setup code here, to run once:
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

#### Referancing: To get the memory address of a variable, use address-of operator (&), aka referencing operator. 
- &: a unary operator that returns lvalue of variable
- To assign a pointer to a location; ```myPointer = &myVar```

#### Dereferancing aka indirection: used to obtain/get/change the main variables value
- it occurs when there's no data type in front of a variable 
- eg. 
```
int * pX = &x //integer of pointer px is equal to the memory locaiton of variable x -->referancing
int y = *pX;  // interger y is set to the thing set by pointer pX (essentially 2 steps back) -->derefernacing
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
- to make two arrays go off at the samwe timwe
```
int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // the notes of the melody
int duration[] = {200, 200, 200, 200, 200, 200, 200, 200}; // the duration of each note
int melodyLength = sizeof(melody) / sizeof(int); // the length of the melody

  for (int i = 0; i < melodyLength; i++) {
    int* p_note = &melody[i]; // create a pointer to the current note
    int* p_duration = &duration[i]; // create a pointer to the current note duration
    
    tone(speakerPin, *p_note, *p_duration); // play the current note
    
```
### Terminology
- Core files: These are pieces of code that are built into the Arduino IDE eg. digitalWrite, digitalRead, delay
- Registers are ... that help to improve the speed and descrease the memory storage place within a microcontroller. More difficult to read. 

## Further study

### Links
- https://engineerworkshop.com/blog/pointers-arrays-and-functions-in-arduino-c/: how to use pointers (array[need documentation], functions[confusing])
- https://reefwing.medium.com/pointers-in-c-and-c-for-arduino-911ab1afe82e: confusing
- https://cplusplus.com/doc/tutorial/: list of all terminology
- https://www.youtube.com/watch?v=QyKVbQH4Hi4&list=PLKL6KBeCnI3X7cb1sznYuyScUesOxS-kL: registers with tinkercad
### Terms that I have no clue about + kinda need to know

#### Pointers
- how pointers can be used to make a struc be in scope of a function
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
- metasynactic variables
- STL
