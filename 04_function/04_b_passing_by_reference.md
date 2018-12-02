# Reference 

A simple assignment statement.
~~~
int a = 10;
int b = a;                  //just create a data object, named b and its value is the same as a. is 10. just a deep copy operation.
b ++
std::cout << b << std::endl; // output is 11
std::cout << a << std::endl; // output is 10
~~~

how to create a shadow copy of a variable? that means, if we do a operation to the copy, the sampel operation will occure to the initial variable.

this is a reference variable.

A refernece is a name that acts as an alias, or an alternative name, for a previously defined variable.
~~~
int a = 10;
int& b = a;  // make a shadow copy to a
b ++
std::cout << b << std::endl;   // 11
std::cout << a << std::endl;   // 11
~~~

In this context, & is not the address operator. Instead, it serves as part of the type identifier. int& means its a shadow copy of a int variable.

# passing by a reference to
