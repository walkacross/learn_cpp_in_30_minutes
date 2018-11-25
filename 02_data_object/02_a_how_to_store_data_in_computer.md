# how to store data in computer
when you define a data in computer, the computer will create an data object in memory to record the infomation of this daa. that means, A data is an object that has many attributes to represent all aspects of this data.
~~~
data_object.name
data_object.value
data_object.type
data_object.size
data_object.store_address
~~~

## declaration statement
~~~
int carrots
~~~
declaration statment set parts of attributes to this data object
~~~
data_object.name = carrots
data_object.type = 'int'
data_object.size = 4 bytes
data_object.store_address = #00023B
~~~

## assignment statement
~~~
carrots = 25
~~~

assignment statement set the value attribute to this data object

~~~
data_object.value = 25
~~~

actually you can combine these two steps into one
~~~
int carrots = 25
~~~

# how to access the attributes of a data object

## 1 access the value of a data object
just enter the name of the data object
~~~
std::cout << the value of the data object is : << carrots << std:endl
~~~

## 2 access the size of a data object
sizeof(x) returns the size of data object (in bytes) that the data objec occupies in memory
~~~
std::cout << the size of the data object is : << sizeof(carrots) << std::endl
~~~

## 3 acces the address in memory of a data object
& will extract the memory address of a data object
~~~
std::cout << the address of carrots in memory is : << &carrot << std::endl
~~~
