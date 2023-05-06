# USE
- turtle.done() = use for vscode to keep the display, turtle.screen(), turtle.getscreen are useless for vscode, only use for void
- 


## To do before next class
- python w3school| python strongs: excerise 4

# Notes
- tuples is surrounded by (), ROM (read only memory)
- lists is characterised by []; they can be have different data types; can be changed
- tuples and lists are similar to each other
- dictionary (array) is {}
- string (); for only the char data type

- comment for one line (#)
- comment for several lines (""" """)
- global variables ```global [variable]```

```
print (str) # Prints complete string
print (str[0]) # Prints first character of the string
print (str[2:5]) # Prints characters starting from 3rd to 5th
print (str[2:]) # Prints string starting from 3rd character
print (str * 2) # Prints string two times
print (str + "TEST") # Prints concatenated string

This will produce the following result-
Hello World!
H
llo
llo World!
Hello World!Hello World!
Hello World!TEST
```
### len()
- len() = is to find the lengh of a string, list, tuples
```
>>> greeting = "Good Day!"
>>> len(greeting)
9

>>> office_days = ["Tuesday", "Thursday", "Friday"]
>>> len(office_days)
3

>>> london_coordinates = (51.50722, -0.1275)
>>> len(london_coordinates)
2
```
## strings
- .strip() = remove whitespace at end or beginning
- .upper() = change val to upper
- .replace("x","y")
- ```{}``` is to add a placeholder in a string

## Lists
- also known as sequence
- use []
- do not need to be the same type
- referance: list[1]
- to delete ```del list[2]```
- to update ```list[2] = new_value

## dictionaries
- are lists that have a key that you can referance instead of a number
- when referancing only referance the key not the value
- adding a key: dict["key"]= string, int and float !lists
- inclusion operator (in): ```"key1" in dict``` --> checks if the key exists in dictionatary
- 
- to delete ```del dictname['dict key']```
- to update ```dictname['dict key'] = new_value
- to get a list of values ```dictname.values()```
- to remove all elements of dictionary ```dictname.clear()```
- these can be updated, deleted
```
dict = {'Name': 'Bob','Age': '7'}
print "dict['Name']:", dict['Name']
```
## Tuples
- are lists that cannot be changed later 
- use ()
- do not need to be the same type
- to access values ```print "tup1[0]: ", tup1[0];```
- to access a select number of values ```print "tup2[1:5]: ", tup2[1:5]; --> tup2[1:5]:  [2, 3, 4, 5]```
- to update: impossible ```VOID```
- to delete: ```del tupname```

### Basic Operations (used for tuples and lists)
- lengh of tuple: len(tuplename)
- concatenation:``` var1 = tupl +tup2```
- repetition: ```('Hi!',) * 4 --> ('Hi!', 'Hi!', 'Hi!', 'Hi!')```
- membership (to check if a value is in tuple): ```3 in (tuple[1, 2, 3]) --> TRUE```
- iteration: ```for x in (tuple[1, 2, 3]): print x --> 1 2 3```


## Functions for lists, dict and tuples
- len(dict): gives number of items in dictionary
- len(tuple):
- cmp(dict1, dict2): compares elements of both dictionaries
- cmp(tuple1,tuple2)
- cmp)list1, list2)
- max(tuple):returns tuple with the max value
- max(list)
- min(tuple): returns tuple with the min value
- min(list)
- tuple(seq): coverts list into a tuple
- list(seq)
- str(dict): string repersentaiton of dict
- type(variable): returns the passed variable
- 
- type(variable): returns the type nof passed variable eg. dictionary type

- slicing (only for tuple and string): name[1:] -->everything besides vaslue 0
- indexing (only for tuple and string): ```L[-2]``` --> negative minus two from variable 0
- sequencing (only for tuple and string): ```L[2]``` --> normal 3rd value
