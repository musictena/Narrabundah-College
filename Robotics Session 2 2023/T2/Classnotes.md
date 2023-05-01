# Class topics



## Variable recap
- memory address (aka location value is lvalue); used to store location of value for compiler
- stored data (aka register value is rvalue); is used to store the specific data in the memory  

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
- THe use of static and dynamic memory allocation
### Pointer Arduino example 
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
### Further study
- https://engineerworkshop.com/blog/pointers-arrays-and-functions-in-arduino-c/: how to use pointers (array[need documentation], functions[confusing])
- https://reefwing.medium.com/pointers-in-c-and-c-for-arduino-911ab1afe82e: confusing
