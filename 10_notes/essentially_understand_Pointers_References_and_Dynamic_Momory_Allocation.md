# essentially understand Pointers, References and Dynamic Momory Allocation

***Pointers, References and Dynamic Memory Allocation*** are the most powerful features in C/C++ language, which allows programmers to directly manipulate memory to efficiently manage the memory - the most critical and scarce resource in computer - for best performance. However, "pointer" is also the most complex and difficult feature in C/C++ language.

Pointers are extremely powerful because they allows you to access addresses and manipulate their contents. But they are also extremely complex to handle. Using them correctly, they could greatly improve the efficiency and performance. On the other hand, using them incorrectly could lead to many problems, from un-readable and un-maintainable codes, to infamous bugs such as memory leaks and buffer overflow, which may expose your system to hacking. Many new languages (such as Java and C#) remove pointer from their syntax to avoid the pitfalls of pointers, by providing automatic memory management.

Although you can write C/C++ programs without using pointers, however, it is difficult not to mention pointer in teaching C/C++ language. Pointer is probably not meant for novices and dummies.

# 1 Pointer Variables

A computer memory location has an address and holds a content. The address is a numerical number (often expressed in hexadecimal), which is hard for programmers to use directly. Typically, each address location holds 8-bit (i.e., 1-byte) of data. It is entirely up to the programmer to interpret the meaning of the data, such as integer, real number, characters or strings.

To ease the burden of programming using numerical address and programmer-interpreted data, early programming languages (such as C) introduce the concept of variables. A variable is a named location that can store a value of a particular type. Instead of numerical addresses, names (or identifiers) are attached to certain addresses. Also, types (such as int, double, char) are associated with the contents for ease of interpretation of data.

Each address location typically hold 8-bit (i.e., 1-byte) of data. A 4-byte int value occupies 4 memory locations. A 32-bit system typically uses 32-bit addresses. To store a 32-bit address, 4 memory locations are required.

The following diagram illustrate the relationship between computers' memory address and content; and variable's name, type and value used by the programmers.

## 1.1 essence and definition of Pointer Variables (or Pointers)

> A pointer variable (or pointer in short) is basically the same as the other variables, which can store a piece of data. Unlike normal variable which stores a value (such as an int, a double, a char), a pointer stores a memory address.

## 1.2 Declaring Pointers
Pointers must be declared before they can be used, just like a normal variable. The syntax of declaring a pointer is to place a * in front of the name. A pointer is associated with a type (such as int and double) too.
~~~
type *ptr;   // Declare a pointer variable called ptr as a pointer of type
// or
type* ptr;
// or
type * ptr;  // I shall adopt this convention
~~~

for example
~~~
int * iPtr;     // Declare a pointer variable called iPtr pointing to an int (an int pointer)
                // It contains an address. That address holds an int value.
double * dPtr;  // Declare a double pointer
~~~

Take note that you need to place a * in front of each pointer variable, in other words, * applies only to the name that followed. The * in the declaration statement is not an operator, but indicates that the name followed is a pointer variable. For example,
~~~
int *p1, *p2, i;    // p1 and p2 are int pointers. i is an int
int* p1, p2, i;     // p1 is a int pointer, p2 and i are int
int * p1, * p2, i;  // p1 and p2 are int pointers, i is an int
~~~

> Naming Convention of Pointers: Include a "p" or "ptr" as prefix or suffix, e.g., iPtr, numberPtr, pNumber, pStudent.

## 1.3  Initializing Pointers via the Address-Of Operator (&)
When you declare a pointer variable, its content is not initialized. In other words, it contains an address of "somewhere", which is of course not a valid location. This is dangerous! You need to initialize a pointer by assigning it a valid address. This is normally done via the address-of operator (&).

The address-of operator (&) operates on a variable, and returns the address of the variable. For example, if number is an int variable, &number returns the address of the variable number.

You can use the address-of operator to get the address of a variable, and assign the address to a pointer variable. For example,
~~~
int number = 88;     // An int variable with a value
int * pNumber;       // Declare a pointer variable called pNumber pointing to an int (or int pointer)
pNumber = &number;   // Assign the address of the variable number to pointer pNumber
 
int * pAnother = &number; // Declare another int pointer and init to address of the variable number
~~~
As illustrated, the int variable number, starting at address 0x22ccec, contains an int value 88. The expression &number returns the address of the variable number, which is 0x22ccec. This address is then assigned to the pointer variable pNumber, as its initial value.

The address-of operator (&) can only be used on the RHS.

## 1.4 Indirection or Dereferencing Operator (*)
The indirection operator (or dereferencing operator) (*) operates on a pointer, and returns the value stored in the address kept in the pointer variable. For example, if pNumber is an int pointer, *pNumber returns the int value "pointed to" by pNumber.

For example,
~~~
int number = 88;
int * pNumber = &number;  // Declare and assign the address of variable number to pointer pNumber (0x22ccec)
cout << pNumber<< endl;   // Print the content of the pointer variable, which contain an address (0x22ccec)
cout << *pNumber << endl; // Print the value "pointed to" by the pointer, which is an int (88)
*pNumber = 99;            // Assign a value to where the pointer is pointed to, NOT to the pointer variable
cout << *pNumber << endl; // Print the new value "pointed to" by the pointer (99)
cout << number << endl;   // The value of variable number changes as well (99)
~~~

Take note that pNumber stores a memory address location, whereas *pNumber refers to the value stored in the address kept in the pointer variable, or the value pointed to by the pointer.

As illustrated, a variable (such as number) directly references a value, whereas a pointer indirectly references a value through the memory address it stores. Referencing a value indirectly via a pointer is called indirection or dereferencing.

The indirection operator (*) can be used in both the RHS (temp = *pNumber) and the LHS (*pNumber = 99) of an assignment statement.

Take note that the symbol * has different meaning in a declaration statement and in an expression. When it is used in a declaration (e.g., int * pNumber), it denotes that the name followed is a pointer variable. Whereas when it is used in a expression (e.g., *pNumber = 99; temp << *pNumber;), it refers to the value pointed to by the pointer variable.

## 1.5  Pointer has a Type Too
A pointer is associated with a type (of the value it points to), which is specified during declaration. A pointer can only hold an address of the declared type; it cannot hold an address of a different type.
~~~
int i = 88;
double d = 55.66;
int * iPtr = &i;    // int pointer pointing to an int value
double * dPtr = &d; // double pointer pointing to a double value
 
iPtr = &d;   // ERROR, cannot hold address of different type
dPtr = &i;   // ERROR
iPtr = i;    // ERROR, pointer holds address of an int, NOT int value
 
int j = 99;
iPtr = &j;  // You can change the address stored in a pointer
~~~

example
~~~
/* Test pointer declaration and initialization (TestPointerInit.cpp) */
#include <iostream>
using namespace std;
 
int main() {
   int number = 88;    // Declare an int variable and assign an initial value
   int * pNumber;      // Declare a pointer variable pointing to an int (or int pointer)
   pNumber = &number;  // assign the address of the variable number to pointer pNumber
 
   cout << pNumber << endl;  // Print content of pNumber (0x22ccf0)
   cout << &number << endl;  // Print address of number (0x22ccf0)
   cout << *pNumber << endl; // Print value pointed to by pNumber (88)
   cout << number << endl;   // Print value of number (88)
 
   *pNumber = 99;            // Re-assign value pointed to by pNumber
   cout << pNumber << endl;  // Print content of pNumber (0x22ccf0)
   cout << &number << endl;  // Print address of number (0x22ccf0)
   cout << *pNumber << endl; // Print value pointed to by pNumber (99)
   cout << number << endl;   // Print value of number (99)
                             // The value of number changes via pointer
 
   cout << &pNumber << endl; // Print the address of pointer variable pNumber (0x22ccec)
}
~~~

> Notes: The address values that you get are unlikely to be the same as mine. The OS loads the program in available free memory locations, instead of fixed memory locations.

## 1.6  Uninitialized Pointers
The following code fragment has a serious logical error!
~~~
int * iPtr;
*iPtr = 55;
cout << *iPtr << endl;
~~~

The pointer iPtr was declared without initialization, i.e., it is pointing to "somewhere" which is of course an invalid memory location. The *iPtr = 55 corrupts the value of "somewhere"! You need to initialize a pointer by assigning it a valid address. Most of the compilers does not signal an error or a warning for uninitialized pointer?!

## 1.7 Null Pointers
You can initialize a pointer to 0 or NULL, i.e., it points to nothing. It is called a null pointer. Dereferencing a null pointer (*p) causes an STATUS_ACCESS_VIOLATION exception.
~~~
int * iPtr = 0;         // Declare an int pointer, and initialize the pointer to point to nothing
cout << *iPtr << endl;  // ERROR! STATUS_ACCESS_VIOLATION exception
 
int * p = NULL;         // Also declare a NULL pointer points to nothing
~~~
Initialize a pointer to null during declaration is a good software engineering practice.

C++11 introduces a new keyword called nullptr to represent null pointer.


# 2 Reference Variables
C++ added the so-called reference variables (or references in short). A reference is an alias, or an alternate name to an existing variable. For example, suppose you make peter a reference (alias) to paul, you can refer to the person as either peter or paul.

The main use of references is acting as function formal parameters to support pass-by-reference. In an reference variable is passed into a function, the function works on the original copy (instead of a clone copy in pass-by-value). Changes inside the function are reflected outside the function.

A reference is similar to a pointer. In many cases, a reference can be used as an alternative to pointer, in particular, for the function parameter.

## 2.1  References (or Aliases) (&)
Recall that C/C++ use & to denote the address-of operator in an expression. C++ assigns an additional meaning to & in declaration to declare a reference variable.

The meaning of symbol & is different in an expression and in a declaration. When it is used in an expression, & denotes the address-of operator, which returns the address of a variable, e.g., if number is an int variable, &number returns the address of the variable number (this has been described in the above section).

Howeve, when & is used in a declaration (including function formal parameters), it is part of the type identifier and is used to declare a reference variable (or reference or alias or alternate name). It is used to provide another name, or another reference, or alias to an existing variable.

The syntax is as follow:
~~~
type &newName = existingName;
// or
type& newName = existingName;
// or
type & newName = existingName;  // I shall adopt this convention
~~~

It shall be read as "newName is a reference to exisitngName", or "newNew is an alias of existingName". You can now refer to the variable as newName or existingName.

For example,
~~~
/* Test reference declaration and initialization (TestReferenceDeclaration.cpp) */
#include <iostream>
using namespace std;
 
int main() {
   int number = 88;          // Declare an int variable called number
   int & refNumber = number; // Declare a reference (alias) to the variable number
                             // Both refNumber and number refer to the same value
 
   cout << number << endl;    // Print value of variable number (88)
   cout << refNumber << endl; // Print value of reference (88)
 
   refNumber = 99;            // Re-assign a new value to refNumber
   cout << refNumber << endl;
   cout << number << endl;    // Value of number also changes (99)
 
   number = 55;               // Re-assign a new value to number
   cout << number << endl;
   cout << refNumber << endl; // Value of refNumber also changes (55)
}

~~~

## 2.2  How References Work?
A reference works as a pointer. A reference is declared as an alias of a variable. It stores the address of the variable, as illustrated:

## 2.3 References vs. Pointers
Every reference has a dual nature: It’s implemented under the covers as a pointer, but semantically it usually behaves like an alias because most uses of its name automatically dereference it.

Pointers and references are equivalent, except:

1. A reference is a name constant for an address. You need to initialize the reference during declaration.
~~~
int & iRef;   // Error: 'iRef' declared as reference but not initialized
~~~
Once a reference is established to a variable, you cannot change the reference to reference another variable.

2. To get the value pointed to by a pointer, you need to use the dereferencing operator * (e.g., if pNumber is a int pointer, *pNumber returns the value pointed to by pNumber. It is called dereferencing or indirection). To assign an address of a variable into a pointer, you need to use the address-of operator & (e.g., pNumber = &number).
On the other hand, referencing and dereferencing are done on the references implicitly. For example, if refNumber is a reference (alias) to another int variable, refNumber returns the value of the variable. No explicit dereferencing operator * should be used. Furthermore, to assign an address of a variable to a reference variable, no address-of operator & is needed.

for example
~~~
/* References vs. Pointers (TestReferenceVsPointer.cpp) */
#include <iostream>
using namespace std;
 
int main() {
   int number1 = 88, number2 = 22;
 
   // Create a pointer pointing to number1
   int * pNumber1 = &number1;  // Explicit referencing
   *pNumber1 = 99;             // Explicit dereferencing
   cout << *pNumber1 << endl;  // 99
   cout << &number1 << endl;   // 0x22ff18
   cout << pNumber1 << endl;   // 0x22ff18 (content of the pointer variable - same as above)
   cout << &pNumber1 << endl;  // 0x22ff10 (address of the pointer variable)
   pNumber1 = &number2;        // Pointer can be reassigned to store another address
 
   // Create a reference (alias) to number1
   int & refNumber1 = number1;  // Implicit referencing (NOT &number1)
   refNumber1 = 11;             // Implicit dereferencing (NOT *refNumber1)
   cout << refNumber1 << endl;  // 11
   cout << &number1 << endl;    // 0x22ff18
   cout << &refNumber1 << endl; // 0x22ff18
   //refNumber1 = &number2;     // Error! Reference cannot be re-assigned
                                // error: invalid conversion from 'int*' to 'int'
   refNumber1 = number2;        // refNumber1 is still an alias to number1.
                                // Assign value of number2 (22) to refNumber1 (and number1).
   number2++;   
   cout << refNumber1 << endl;  // 22
   cout << number1 << endl;     // 22
   cout << number2 << endl;     // 23
}
~~~
A reference variable provides a new name to an existing variable. It is dereferenced implicitly and does not need the dereferencing operator * to retrieve the value referenced. On the other hand, a pointer variable stores an address. You can change the address value stored in a pointer. To retrieve the value pointed to by a pointer, you need to use the indirection operator *, which is known as explicit dereferencing. Reference can be treated as a const pointer. It has to be initialized during declaration, and its content cannot be changed.

Reference is closely related to pointer. In many cases, it can be used as an alternative to pointer. A reference allows you to manipulate an object using pointer, but without the pointer syntax of referencing and dereferencing.

The above example illustrates how reference works, but does not show its typical usage, which is used as the function formal parameter for pass-by-reference.

# 3 Arguments passing techniques in c++
The Main objective of passing Argument to function is Message passing. The message passing is also known as communication between two functions, that is between a caller and called functions. 

In common usage, the terms parameter and argument are often interchanged. However, for the purposes of further discussion, we will make a distinction between the two:
* A function parameter (sometimes called a formal parameter) is a variable declared in the function declaration:
~~~
void foo(int x); // declaration (function prototype) -- x is a parameter
 
void foo(int x) // definition (also a declaration) -- x is a parameter
{
}
~~~
* An argument (sometimes called an actual parameter) is the value that is passed to the function by the caller:
~~~
foo(6); // 6 is the argument passed to parameter x
foo(y+1); // the value of y+1 is the argument passed to parameter x
~~~
When a function is called, all of the parameters of the function are created as variables, and the value of the arguments are copied into the parameters. For example:
~~~
void foo(int x, int y)
{
}
 
foo(6, 7);
~~~
When foo() is called with arguments 6 and 7, foo’s parameter x is created and assigned the value of 6, and foo’s parameter y is created and assigned the value of 7.

> **Even though parameters are not declared inside the function block, function parameters have local scope. This means that they are created when the function is invoked, and are destroyed when the function block terminates:**
~~~
void foo(int x, int y) // x and y are created here
{
} // x and y are destroyed here
~~~
There are 3 primary methods of passing arguments to functions: pass by value, pass by reference, and pass by address.


There are three Methods by which we can pass message to the function. These Methods are as follows:

1. pass-by-value
2. pass-by-pointer
3. pass-by-reference

## 3.1 pass-by-value
In C/C++, by default, arguments are passed into functions by value (except arrays which is treated as pointers). That is, a clone copy of the argument is made and passed into the function. Changes to the clone copy inside the function has no effect to the original argument in the caller. In other words, the called function has no access to the variables in the caller. For example,

~~~
#include <iostream>
 
void foo(int y)
{
    std::cout << "y = " << y << '\n';
 
    y = 6;
 
    std::cout << "y = " << y << '\n';
} // y is destroyed here
 
int main()
{
    int x{ 5 };
    std::cout << "x = " << x << '\n';
 
    foo(x);
 
    std::cout << "x = " << x << '\n';
    return 0;
}
~~~
This snippet outputs:
~~~
x = 5
y = 5
y = 6
x = 5
~~~
At the start of main, x is 5. When foo() is called, the value of x (5) is passed to foo’s parameter y. Inside foo(), y is assigned the value of 6, and then destroyed. The value of x is unchanged, even though y was changed.

Function parameters passed by value can also be made const. This will enlist the compiler’s help in ensuring the function doesn’t try to change the parameter’s value.


~~~
/* Pass-by-value into function (TestPassByValue.cpp) */
#include <iostream>
using namespace std;
 
int square(int);
 
int main() {
   int number = 8;
   cout <<  "In main(): " << &number << endl;  // 0x22ff1c
   cout << number << endl;         // 8
   cout << square(number) << endl; // 64
   cout << number << endl;         // 8 - no change
}
 
int square(int n) {  // non-const
   cout <<  "In square(): " << &n << endl;  // 0x22ff00
   n *= n;           // clone modified inside the function
   return n;
}
~~~
The output clearly shows that there are two different addresses.

### Pros and cons of pass by value

### Advantages of passing by value:

Arguments passed by value can be variables (e.g. x), literals (e.g. 6), expressions (e.g. x+1), structs & classes, and enumerators. In other words, just about anything.
Arguments are never changed by the function being called, which prevents side effects.

* Disadvantages of passing by value:

Copying structs and classes can incur a significant performance penalty, especially if the function is called many times.

* When to use pass by value:

When passing fundamental data types and enumerators, and the function does not need to change the argument.

* When not to use pass by value:

When passing structs or classes (including std::array, std::vector, and std::string).
In most cases, pass by value is the best way to accept parameters of fundamental types when the function does not need to change the argument. Pass by value is flexible and safe, and in the case of fundamental types, efficient.


## 3.2 pass-by-pointer
In many situations, we may wish to modify the original copy directly (especially in passing huge object or array) to avoid the overhead of cloning. This can be done by passing a pointer of the object into the function, known as pass-by-pointer. For example,
~~~
/* Pass-by-reference using pointer (TestPassByPointer.cpp) */
#include <iostream>
using namespace std;
 
void square(int *);
 
int main() {
   int number = 8;
   cout <<  "In main(): " << &number << endl;  // 0x22ff1c
   cout << number << endl;   // 8
   square(&number);          // Explicit referencing to pass an address
   cout << number << endl;   // 64
}
 
void square(int * pNumber) {  // Function takes an int pointer (non-const)
   cout <<  "In square(): " << pNumber << endl;  // 0x22ff1c
   *pNumber *= *pNumber;      // Explicit de-referencing to get the value pointed-to
}
~~~

## 3.3 pass-by-reference
While pass by value is suitable in many cases, it has a couple of limitations. First, when passing a large struct or class to a function, pass by value will make a copy of the argument into the function parameter. In many cases, this is a needless performance hit, as the original argument would have sufficed. Second, when passing arguments by value, the only way to return a value back to the caller is via the function’s return value. While this is often suitable, there are cases where it would be more clear and efficient to have the function modify the argument passed in. Pass by reference solves both of these issues.

Pass by reference

Instead of passing pointers into function, you could also pass references into function, to avoid the clumsy syntax of referencing and dereferencing. For example,
~~~
/* Pass-by-reference using reference (TestPassByReference.cpp) */
#include <iostream>
using namespace std;
 
void square(int &);
 
int main() {
   int number = 8;
   cout <<  "In main(): " << &number << endl;  // 0x22ff1c
   cout << number << endl;  // 8
   square(number);          // Implicit referencing (without '&')
   cout << number << endl;  // 64
}
 
void square(int & rNumber) {  // Function takes an int reference (non-const)
   cout <<  "In square(): " << &rNumber << endl;  // 0x22ff1c
   rNumber *= rNumber;        // Implicit de-referencing (without '*')
}
~~~
Again, the output shows that the called function operates on the same address, and can thus modify the caller's variable.

Take note referencing (in the caller) and dereferencing (in the function) are done implicitly. The only coding difference with pass-by-value is in the function's parameter declaration.

Recall that references are to be initialized during declaration. In the case of function formal parameter, the references are initialized when the function is invoked, to the caller's arguments.

References are primarily used in passing reference in/out of functions to allow the called function accesses variables in the caller directly.

* Advantages of passing by reference:
~~~
References allow a function to change the value of the argument, which is sometimes useful. Otherwise, const references can be used to guarantee the function won’t change the argument.
Because a copy of the argument is not made, pass by reference is fast, even when used with large structs or classes.
References can be used to return multiple values from a function (via out parameters).
References must be initialized, so there’s no worry about null values.
~~~

* Disadvantages of passing by reference:

Because a non-const reference cannot be initialized with a const l-value or an r-value (e.g. a literal or an expression), arguments to non-const reference parameters must be normal variables.
It can be hard to tell whether an argument passed by non-const reference is meant to be input, output, or both. Judicious use of const and a naming suffix for out variables can help.
It’s impossible to tell from the function call whether the argument may change. An argument passed by value and passed by reference looks the same. We can only tell whether an argument is passed by value or reference by looking at the function declaration. This can lead to situations where the programmer does not realize a function will change the value of the argument.
When to use pass by reference:
~~~
When passing structs or classes (use const if read-only).
When you need the function to modify an argument.
When you need access to the type information of a fixed array.
When not to use pass by reference:
~~~
When passing fundamental types that don’t need to be modified (use pass by value).


## 3.4 *const* Function Reference/Pointer Parameters
A *const* function formal parameter cannot be modified inside the function. Use const whenever possible as it protects you from inadvertently modifying the parameter and protects you against many programming errors.

A *const* function parameter can receive both const and non-const argument. On the other hand, a non-const function reference/pointer parameter can only receive non-const argument. For example,
~~~
/* Test Function const and non-const parameter (FuncationConstParameter.cpp) */
#include <iostream>
using namespace std;
 
int squareConst(const int);
int squareNonConst(int);
int squareConstRef(const int &);
int squareNonConstRef(int &);
 
int main() {
   int number = 8;
   const int constNumber = 9;
   cout << squareConst(number) << endl;
   cout << squareConst(constNumber) << endl;
   cout << squareNonConst(number) << endl;
   cout << squareNonConst(constNumber) << endl;
 
   cout << squareConstRef(number) << endl;
   cout << squareConstRef(constNumber) << endl;
   cout << squareNonConstRef(number) << endl;
   // cout << squareNonConstRef(constNumber) << endl;
       // error: invalid initialization of reference of
       //  type 'int&' from expression of type 'const int'
}
 
int squareConst(const int number) {
   // number *= number;  // error: assignment of read-only parameter
   return number * number;
}
 
int squareNonConst(int number) {  // non-const parameter
   number *= number;
   return number;
}
 
int squareConstRef(const int & number) {  // const reference
   return number * number;
}
 
int squareNonConstRef(int & number) {  // non-const reference
   return number * number;
}
~~~

## understand how arguments passing really work
### a: Addresses are actually passed by value

When you pass a pointer to a function, the pointer’s value (the address it points to) is copied from the argument to the function’s parameter. In other words, it’s passed by value! If you change the function parameter’s value, you are only changing a copy. Consequently, the original pointer argument will not be changed.

Here’s a sample program that illustrates this.
~~~
#include <iostream>
 
void setToNull(int* tempPtr)
{
    // we're making tempPtr point at something else, not changing the value that tempPtr points to.
    tempPtr = nullptr; // use 0 instead if not C++11
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr will receive a copy of ptr
    setToNull(ptr);
 
    // ptr is still set to the address of five!
 
    // This will print 5
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~
tempPtr receives a copy of the address that ptr is holding. Even though we change tempPtr to point at something else (nullptr), this does not change the value that ptr points to. Consequently, this program prints:
~~~
55
~~~

Note that even though the address itself is passed by value, you can still dereference that address to change the argument’s value. This is a common point of confusion, so let’s clarify:

When passing an argument by address, the function parameter variable receives a copy of the address from the argument. At this point, the function parameter and the argument both point to the same value.
* If the function parameter is then dereferenced to change the value being pointed to, that will impact the value the argument is pointing to, since both the function parameter and argument are pointing to the same value!
* If the function parameter is assigned a different address, that will not impact the argument, since the function parameter is a copy, and changing the copy won’t impact the original. After changing the function parameter’s address, the function parameter and argument will point to different values, so dereferencing the parameter and changing the value will no longer affect the value pointed to by the argument.

The following program illustrates the point:
~~~
#include <iostream>
 
void setToSix(int* tempPtr)
{
    *tempPtr = 6; // we're changing the value that tempPtr (and ptr) points to
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr will receive a copy of ptr
    setToSix(ptr);
 
    // tempPtr changed the value being pointed to to 6, so ptr is now pointing to the value 6
 
    // This will print 6
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~

This prints:
~~~
56
~~~

### b: Passing addresses by reference
The next logical question is, “What if we want to change the address an argument points to from within the function?”. Turns out, this is surprisingly easy. You can simply pass the address by reference. The syntax for doing a reference to a pointer is a little strange (and easy to get backwards). However, if you do get it backwards, the compiler will give you an error.

The following program illustrates using a reference to a pointer:
~~~
#include <iostream>
 
// tempPtr is now a reference to a pointer, so any changes made to tempPtr will change the argument as well!
void setToNull(int*& tempPtr)
{
    tempPtr = nullptr; // use 0 instead if not C++11
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr is set as a reference to ptr
    setToNull(ptr);
 
    // ptr has now been changed to nullptr!
 
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~
When we run the program again with this version of the function, we get:
~~~
5 ptr is null
~~~

Which shows that calling setToNull() did indeed change the value of ptr from &five to nullptr!

### c: There is only pass by value

Now that you understand the basic differences between passing by reference, address, and value, let’s get reductionist for a moment. :)

In the lesson on references, we briefly mentioned that references are typically implemented by the compiler as pointers. This means that behind the scenes, pass by reference is essentially just a pass by address (with access to the reference doing an implicit dereference).

And just above, we showed that pass by address is actually just passing an address by value!

Therefore, we can conclude that C++ really passes everything by value! The properties of pass by address (and reference) come solely from the fact that we can dereference the passed address to change the argument, which we can not do with a normal value parameter!

# 4 Passing the Function's Return Value(Returning values by value, reference, and address)
In the three previous lessons, you learned about passing arguments to functions by value, reference, and address. In this section, we’ll consider the issue of returning values back to the caller via all three methods.

As it turns out, returning values from a function to its caller by value, address, or reference works almost exactly the same way as passing arguments to a function does. All of the same upsides and downsides for each method are present. The primary difference between the two is simply that the direction of data flow is reversed. However, there is one more added bit of complexity -- because local variables in a function go out of scope and are destroyed when the function returns, we need to consider the effect of this on each return type.

## 4.1 Return by value
Return by value is the simplest and safest return type to use. When a value is returned by value, a copy of that value is returned to the caller. As with pass by value, you can return by value literals (e.g. 5), variables (e.g. x), or expressions (e.g. x+1), which makes return by value very flexible.

Another advantage of return by value is that you can return variables (or expressions) that involve local variables declared within the function without having to worry about scoping issues. Because the variables are evaluated before the function returns, and a copy of the value is returned to the caller, **there are no problems when the function’s variable goes out of scope at the end of the function.**
~~~
int doubleValue(int x)
{
    int value{ x * 2 };
    return value; // A copy of value will be returned here
} // value goes out of scope here
~~~
Return by value is the most appropriate when returning variables that were declared inside the function, or for returning function arguments that were passed by value. However, like pass by value, return by value is slow for structs and large classes.

When to use return by value:

* When returning variables that were declared inside the function
* When returning function arguments that were passed by value

When not to use return by value:

* When returning a built-in array or pointer (use return by address)
* When returning a large struct or class (use return by reference)

## 4.2 Return by address

Returning by address involves returning the address of a variable to the caller. Similar to pass by address, return by address can only return the address of a variable, not a literal or an expression (which don’t have addresses). Because return by address just copies an address from the function to the caller, return by address is fast.

However, return by address has one additional downside that return by value doesn’t -- if you try to return the address of a variable local to the function, your program will exhibit undefined behavior. Consider the following example:
~~~
int* doubleValue(int x)
{
    int value{ x * 2 };
    return &value; // return value by address here
} // value destroyed here
~~~
As you can see here, value is destroyed just after its address is returned to the caller. The end result is that the caller ends up with the address of non-allocated memory (a dangling pointer), which will cause problems if used. This is a common mistake that new programmers make. Many newer compilers will give a warning (not an error) if the programmer tries to return a local variable by address -- however, there are quite a few ways to trick the compiler into letting you do something illegal without generating a warning, so the burden is on the programmer to ensure the pointer they are returning will point to a valid variable after the function returns.

Return by address was often used to return dynamically allocated memory to the caller:
~~~
int* allocateArray(int size)
{
    return new int[size];
}
 
int main()
{
    int *array{ allocateArray(25) };
 
    // do stuff with array
 
    delete[] array;
    return 0;
}
~~~

This works because dynamically allocated memory does not go out of scope at the end of the block in which it is declared, so that memory will still exist when the address is returned back to the caller. Keeping track of manual allocations can be difficult. Separating the allocation and deletion into different functions makes it even harder to understand who’s responsible for deleting the resource or if the resource needs to be deleted at all. Smart pointers (covered later) and types that clean up after themselves should be used instead of manual allocations.

When to use return by address:

* When returning dynamically allocated memory and you can’t use a type that handles allocations for you
* When returning function arguments that were passed by address

When not to use return by address:

* When returning variables that were declared inside the function or parameters that were passed by value (use return by value)
* When returning a large struct or class that was passed by reference (use return by reference)

## 4.3 Return by reference
Similar to return by address, values returned by reference must be variables (you should not return a reference to a literal or an expression that resolves to a temporary value, as those will go out of scope at the end of the function and you’ll end up returning a dangling reference). When a variable is returned by reference, a reference to the variable is passed back to the caller. The caller can then use this reference to continue modifying the variable, which can be useful at times. Return by reference is also fast, which can be useful when returning structs and classes.

However, just like return by address, you should not return local variables by reference. Consider the following example:
~~~
int& doubleValue(int x)
{
    int value{ x * 2 };
    return value; // return a reference to value here
} // value is destroyed here
~~~
In the above program, the program is returning a reference to a value that will be destroyed when the function returns. This would mean the caller receives a reference to garbage. Fortunately, your compiler will probably give you a warning or error if you try to do this.

Return by reference is typically used to return arguments passed by reference to the function back to the caller. In the following example, we return (by reference) an element of an array that was passed to our function by reference:
~~~
#include <array>
#include <iostream>
 
// Returns a reference to the index element of array
int& getElement(std::array<int, 25>& array, int index)
{
    // we know that array[index] will not be destroyed when we return to the caller (since the caller passed in the array in the first place!)
    // so it's okay to return it by reference
    return array[index];
}
 
int main()
{
    std::array<int, 25> array;
 
    // Set the element of array with index 10 to the value 5
    getElement(array, 10) = 5;
	
    std::cout << array[10] << '\n';
 
    return 0;
}
// This prints: 5
~~~

When we call getElement(array, 10), getElement() returns a reference to the array element with index 10. main() then uses this reference to assign that element the value 5.

Although this is somewhat of a contrived example (because you can access array[10] directly), once you learn about classes you will find a lot more uses for returning values by reference.

When to use return by reference:

* When returning a reference parameter
* When returning a member of an object that was passed into the function by reference or address
* When returning a large struct or class that will not be destroyed at the end of the function (e.g. one that was passed in by reference)

When not to use return by reference:

* When returning variables that were declared inside the function or parameters that were passed by value (use return by value)
* When returning a built-in array or pointer value (use return by address)

You can also pass the return-value as reference or pointer. For example,
~~~
/* Passing back return value using reference (TestPassByReferenceReturn.cpp) */
#include <iostream>
using namespace std;
 
int & squareRef(int &);
int * squarePtr(int *);
 
int main() {
   int number1 = 8;
   cout <<  "In main() &number1: " << &number1 << endl;  // 0x22ff14
   int & result = squareRef(number1);
   cout <<  "In main() &result: " << &result << endl;  // 0x22ff14
   cout << result << endl;   // 64
   cout << number1 << endl;  // 64
 
   int number2 = 9;
   cout <<  "In main() &number2: " << &number2 << endl;  // 0x22ff10
   int * pResult = squarePtr(&number2);
   cout <<  "In main() pResult: " << pResult << endl;  // 0x22ff10
   cout << *pResult << endl;   // 81
   cout << number2 << endl;    // 81
}
 
int & squareRef(int & rNumber) {
   cout <<  "In squareRef(): " << &rNumber << endl;  // 0x22ff14
   rNumber *= rNumber;
   return rNumber;
}
 
int * squarePtr(int * pNumber) {
   cout <<  "In squarePtr(): " << pNumber << endl;  // 0x22ff10
   *pNumber *= *pNumber;
   return pNumber;
}
~~~

attention: **You should not pass Function's local variable as return value by reference**
~~~
/* Test passing the result (TestPassResultLocal.cpp) */
#include <iostream>
using namespace std;
 
int * squarePtr(int);
int & squareRef(int);
 
int main() {
   int number = 8;
   cout << number << endl;  // 8
   cout << *squarePtr(number) << endl;  // ??
   cout << squareRef(number) << endl;   // ??
}
 
int * squarePtr(int number) {
   int localResult = number * number;
   return &localResult;
      // warning: address of local variable 'localResult' returned
}
 
int & squareRef(int number) {
   int localResult = number * number;
   return localResult;
      // warning: reference of local variable 'localResult' returned
}
~~~
This program has a serious logical error, as local variable of function is passed back as return value by reference. Local variable has local scope within the function, and its value is destroyed after the function exits. The GCC compiler is kind enough to issue a warning (but not error).

It is safe to return a reference that is passed into the function as an argument. See earlier examples.

**Passing Dynamically Allocated Memory as Return Value by Reference**
Instead, you need to dynamically allocate a variable for the return value, and return it by reference.
~~~
/* Test passing the result (TestPassResultNew.cpp) */
#include <iostream>
using namespace std;
 
int * squarePtr(int);
int & squareRef(int);
 
int main() {
   int number = 8;
   cout << number << endl;  // 8
   cout << *squarePtr(number) << endl;  // 64
   cout << squareRef(number) << endl;   // 64
}
 
int * squarePtr(int number) {
   int * dynamicAllocatedResult = new int(number * number);
   return dynamicAllocatedResult;
}
 
int & squareRef(int number) {
   int * dynamicAllocatedResult = new int(number * number);
   return *dynamicAllocatedResult;
}
~~~


## 4.4 Mixing return references and values
Although a function may return a value or a reference, the caller may or may not assign the result to a variable or reference accordingly. Let’s look at what happens when we mix value and reference types.
~~~
int returnByValue()
{
    return 5;
}
 
int& returnByReference()
{
     static int x{ 5 }; // static ensures x isn't destroyed when the function ends
     return x;
}
 
int main()
{
    int giana{ returnByReference() }; // case A -- ok, treated as return by value
    int& ref{ returnByValue() }; // case B -- compile error since the value is an r-value, and an r-value can't bind to a non-const reference
    const int& cref{ returnByValue() }; // case C -- ok, the lifetime of the return value is extended to the lifetime of cref
 
    return 0;
}
~~~
In case A, we’re assigning a reference return value to a non-reference variable. Because giana isn’t a reference, the return value is copied into giana, as if returnByReference() had returned by value.

In case B, we’re trying to initialize reference ref with the copy of the return value returned by returnByValue(). However, because the value being returned doesn’t have an address (it’s an r-value), this will cause a compile error.

In case C, we’re trying to initialize const reference cref with the copy of the return value returned by returnByValue(). Because const references can bind to r-values, there’s no problem here. Normally, r-values expire at the end of the expression in which they are created -- however, when bound to a const reference, the lifetime of the r-value (in this case, the return value of the function) is extended to match the lifetime of the reference (in this case, cref)

**Lifetime extension doesn’t save dangling references** Consider the following program:

~~~
const int& returnByReference()
{
     return 5;
}
 
int main()
{
    const int& ref { returnByReference() }; // runtime error
}
~~~
In the above program, returnByReference() is returning a const reference to a value that will go out of scope when the function ends. This is normally a no-no, as it will result in a dangling reference. However, we also know that assigning a value to a const reference can extend the lifetime of that value. So which takes precedence here? Does 5 go out of scope first, or does ref extend the lifetime of 5?

The answer is that 5 goes out of scope first, then the reference to 5 is copied back to the caller, and then ref extends the lifetime of the now-dangling reference.

However, the following does work as expected:
~~~
const int returnByValue()
{
     return 5;
}
 
int main()
{
    const int& ref { returnByValue() }; // ok, we're extending the lifetime of the copy passed back to main
}
~~~

## 4.5 Returning multiple values
C++ doesn’t contain a direct method for passing multiple values back to the caller. While you can sometimes restructure your code in such a way that you can pass back each data item separately (e.g. instead of having a single function return two values, have two functions each return a single value), this can be cumbersome and unintuitive.

Fortunately, there are several indirect methods that can be used.

As covered in lesson 11.3 -- Passing arguments by reference, out parameters provide one method for passing multiple bits of data back to the caller(called output parameter). **We don’t recommend this method**.

second method involves using a data-only struct:
~~~
#include <iostream>
 
struct S
{
	int m_x;
	double m_y;
};
 
S returnStruct()
{
	S s;
	s.m_x = 5;
	s.m_y = 6.7;
	return s;
}
 
int main()
{
	S s{ returnStruct() };
	std::cout << s.m_x << ' ' << s.m_y << '\n';
 
	return 0;
}
~~~

A **third** way (introduced in C++11) is to use std::tuple. A tuple is a sequence of elements that may be different types, where the type of each element must be explicitly specified.

Here’s an example that returns a tuple, and uses std::get to get the nth element of the tuple (counting from 0):
~~~
#include <tuple>
#include <iostream>
 
std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double
{
	return { 5, 6.7 };
}
 
int main()
{
	std::tuple s{ returnTuple() }; // get our tuple
	std::cout << std::get<0>(s) << ' ' << std::get<1>(s) << '\n'; // use std::get<n> to get the nth element of the tuple (counting from 0)
 
	return 0;
}
~~~

This works identically to the prior example.

You can also use std::tie to unpack the tuple into predefined variables, like so:
~~~
#include <tuple>
#include <iostream>
 
std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double
{
	return { 5, 6.7 };
}
 
int main()
{
	int a;
	double b;
	std::tie(a, b) = returnTuple(); // put elements of tuple in variables a and b
	std::cout << a << ' ' << b << '\n'; 
 
	return 0;
}
~~~

As of C++17, a structured binding declaration can be used to simplify splitting multiple returned values into separate variables:
~~~
#include <tuple>
#include <iostream>
 
std::tuple<int, double> returnTuple() // return a tuple that contains an int and a double
{
	return { 5, 6.7 };
}
 
int main()
{
	auto [a, b]{ returnTuple() }; // used structured binding declaration to put results of tuple in variables a and b
	std::cout << a << ' ' << b << '\n';
 
	return 0;
}
~~~

Using a struct is a better option than a tuple if you’re using the struct in multiple places. However, for cases where you’re just packaging up these values to return and there would be no reuse from defining a new struct, a tuple is a bit cleaner since it doesn’t introduce a new user-defined data type.

Most of the time, return by value will be sufficient for your needs. It’s also the most flexible and safest way to return information to the caller. However, return by reference or address can also be useful, particularly when working with dynamically allocated classes or structs. When using return by reference or address, make sure you are not returning a reference to, or the address of, a variable that will go out of scope when the function returns!



## Summary
Pointers and references are highly complex and difficult to master. But they can greatly improve the efficiency of the programs.

For novices, avoid using pointers in your program. Improper usage can lead to serious logical bugs. However, you need to understand the syntaxes of pass-by-reference with pointers and references, because they are used in many library functions.

* In pass-by-value, a clone is made and passed into the function. The caller's copy cannot be modified.
* In pass-by-reference, a pointer is passed into the function. The caller's copy could be modified inside the function.
* In pass-by-reference with reference arguments, you use the variable name as the argument.
* In pass-by-reference with pointer arguments, you need to use &varName (an address) as the argument.

# 5 Dynamic Memory Allocation
## 5.1  new and delete Operators
Instead of define an int variable (int number), and assign the address of the variable to the int pointer (int *pNumber = &number), the storage can be dynamically allocated at runtime, via a new operator. In C++, whenever you allocate a piece of memory dynamically via new, you need to use delete to remove the storage (i.e., to return the storage to the heap).

The new operation returns a pointer to the memory allocated. The delete operator takes a pointer (pointing to the memory allocated via new) as its sole argument.

For example,
~~~
// Static allocation
int number = 88;
int * p1 = &number;  // Assign a "valid" address into pointer
 
// Dynamic Allocation
int * p2;            // Not initialize, points to somewhere which is invalid
cout << p2 << endl; // Print address before allocation
p2 = new int;       // Dynamically allocate an int and assign its address to pointer
                    // The pointer gets a valid address with memory allocated
*p2 = 99;
cout << p2 << endl;  // Print address after allocation
cout << *p2 << endl; // Print value point-to
delete p2;           // Remove the dynamically allocated storage
~~~
Observe that new and delete operators work on pointer.

To initialize the allocated memory, you can use an initializer for fundamental types, or invoke a constructor for an object. For example,
~~~
// use an initializer to initialize a fundamental type (such as int, double)
int * p1 = new int(88);
double * p2 = new double(1.23);
 
// C++11 brace initialization syntax
int * p1 = new int {88};
double * p2 = new double {1.23};
 
// invoke a constructor to initialize an object (such as Date, Time)
Date * date1 = new Date(1999, 1, 1);  
Time * time1 = new Time(12, 34, 56);
~~~
You can dynamically allocate storage for global pointers inside a function. Dynamically allocated storage inside the function remains even after the function exits. For example,
~~~
// Dynamically allocate global pointers (TestDynamicAllocation.cpp)
#include <iostream>
using namespace std;
 
int * p1, * p2;  // Global int pointers
 
// This function allocates storage for the int*
// which is available outside the function
void allocate() {
   p1 = new int;     // Allocate memory, initial content unknown
   *p1 = 88;         // Assign value into location pointed to by pointer
   p2 = new int(99); // Allocate and initialize
}
 
int main() {
   allocate();
   cout << *p1 << endl;  // 88
   cout << *p2 << endl;  // 99
   delete p1;  // Deallocate
   delete p2;
   return 0;
}
~~~

The main differences between static allocation and dynamic allocations are:

1. In static allocation, the compiler allocates and deallocates the storage automatically, and handle memory management. Whereas in dynamic allocation, you, as the programmer, handle the memory allocation and deallocation yourself (via new and delete operators). You have full control on the pointer addresses and their contents, as well as memory management.
2. Static allocated entities are manipulated through named variables. Dynamic allocated entities are handled through pointers.

## 5.2  new[] and delete[] Operators
Dynamic array is allocated at runtime rather than compile-time, via the new[] operator. To remove the storage, you need to use the delete[] operator (instead of simply delete). For example,
~~~
/* Test dynamic allocation of array  (TestDynamicArray.cpp) */
#include <iostream>
#include <cstdlib>
using namespace std;
 
int main() {
   const int SIZE = 5;
   int * pArray;
 
   pArray = new int[SIZE];  // Allocate array via new[] operator
 
   // Assign random numbers between 0 and 99
   for (int i = 0; i < SIZE; ++i) {
      *(pArray + i) = rand() % 100;
   }
   // Print array
   for (int i = 0; i < SIZE; ++i) {
      cout << *(pArray + i) << " ";
   }
   cout << endl;
 
   delete[] pArray;  // Deallocate array via delete[] operator
   return 0;
}
~~~



# Appendix
## Appendix1: function pointer
In C/C++, functions, like all data items, have an address. The name of a function is the starting address where the function resides in the memory, and therefore, can be treated as a pointer. We can pass a function pointer into function as well. The syntax for declaring a function pointer is:

~~~
// Function-pointer declaration
return-type (* function-ptr-name) (parameter-list)
 
// Examples
double (*fp)(int, int)  // fp points to a function that takes two ints and returns a double (function-pointer)
double *dp;             // dp points to a double (double-pointer)
double *fun(int, int)   // fun is a function that takes two ints and returns a double-pointer

double f(int, int);      // f is a function that takes two ints and returns a double
fp = f;                 // Assign function f to fp function-pointer
~~~

example
~~~
/* Test Function Pointers (TestFunctionPointer.cpp) */
#include <iostream>
using namespace std;
 
int arithmetic(int, int, int (*)(int, int));
    // Take 3 arguments, 2 int's and a function pointer
    //   int (*)(int, int), which takes two int's and return an int
int add(int, int);
int sub(int, int);
 
int add(int n1, int n2) { return n1 + n2; }
int sub(int n1, int n2) { return n1 - n2; }
 
int arithmetic(int n1, int n2, int (*operation) (int, int)) {
   return (*operation)(n1, n2);
}
 
int main() {
   int number1 = 5, number2 = 6;
 
   // add
   cout << arithmetic(number1, number2, add) << endl;
   // subtract
   cout << arithmetic(number1, number2, sub) << endl;
}
~~~
## appendix2: how pass-by-pointer really work
### a: Addresses are actually passed by value

When you pass a pointer to a function, the pointer’s value (the address it points to) is copied from the argument to the function’s parameter. In other words, it’s passed by value! If you change the function parameter’s value, you are only changing a copy. Consequently, the original pointer argument will not be changed.

Here’s a sample program that illustrates this.
~~~
#include <iostream>
 
void setToNull(int* tempPtr)
{
    // we're making tempPtr point at something else, not changing the value that tempPtr points to.
    tempPtr = nullptr; // use 0 instead if not C++11
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr will receive a copy of ptr
    setToNull(ptr);
 
    // ptr is still set to the address of five!
 
    // This will print 5
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~
tempPtr receives a copy of the address that ptr is holding. Even though we change tempPtr to point at something else (nullptr), this does not change the value that ptr points to. Consequently, this program prints:
~~~
55
~~~

Note that even though the address itself is passed by value, you can still dereference that address to change the argument’s value. This is a common point of confusion, so let’s clarify:

When passing an argument by address, the function parameter variable receives a copy of the address from the argument. At this point, the function parameter and the argument both point to the same value.
* If the function parameter is then dereferenced to change the value being pointed to, that will impact the value the argument is pointing to, since both the function parameter and argument are pointing to the same value!
* If the function parameter is assigned a different address, that will not impact the argument, since the function parameter is a copy, and changing the copy won’t impact the original. After changing the function parameter’s address, the function parameter and argument will point to different values, so dereferencing the parameter and changing the value will no longer affect the value pointed to by the argument.

The following program illustrates the point:
~~~
#include <iostream>
 
void setToSix(int* tempPtr)
{
    *tempPtr = 6; // we're changing the value that tempPtr (and ptr) points to
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr will receive a copy of ptr
    setToSix(ptr);
 
    // tempPtr changed the value being pointed to to 6, so ptr is now pointing to the value 6
 
    // This will print 6
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~

This prints:
~~~
56
~~~

### b: Passing addresses by reference
The next logical question is, “What if we want to change the address an argument points to from within the function?”. Turns out, this is surprisingly easy. You can simply pass the address by reference. The syntax for doing a reference to a pointer is a little strange (and easy to get backwards). However, if you do get it backwards, the compiler will give you an error.

The following program illustrates using a reference to a pointer:
~~~
#include <iostream>
 
// tempPtr is now a reference to a pointer, so any changes made to tempPtr will change the argument as well!
void setToNull(int*& tempPtr)
{
    tempPtr = nullptr; // use 0 instead if not C++11
}
 
int main()
{ 
    // First we set ptr to the address of five, which means *ptr = 5
    int five{ 5 };
    int* ptr{ &five };
	
    // This will print 5
    std::cout << *ptr;
 
    // tempPtr is set as a reference to ptr
    setToNull(ptr);
 
    // ptr has now been changed to nullptr!
 
    if (ptr)
        std::cout << *ptr;
    else
        std::cout << " ptr is null";
 
    return 0;
}
~~~
When we run the program again with this version of the function, we get:
~~~
5 ptr is null
~~~

Which shows that calling setToNull() did indeed change the value of ptr from &five to nullptr!

### c: There is only pass by value

Now that you understand the basic differences between passing by reference, address, and value, let’s get reductionist for a moment. :)

In the lesson on references, we briefly mentioned that references are typically implemented by the compiler as pointers. This means that behind the scenes, pass by reference is essentially just a pass by address (with access to the reference doing an implicit dereference).

And just above, we showed that pass by address is actually just passing an address by value!

Therefore, we can conclude that C++ really passes everything by value! The properties of pass by address (and reference) come solely from the fact that we can dereference the passed address to change the argument, which we can not do with a normal value parameter!

# reference
https://www3.ntu.edu.sg/home/ehchua/programming/cpp/cp4_PointerReference.html

https://www.learncpp.com/cpp-tutorial/returning-values-by-value-reference-and-address/
