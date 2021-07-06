# Notation about duration, scope and linkage

c++ offers many choices for storing data in memory. you have choices for how long data remainas in memory(**storage duration**) and choice for which parts of a program have access to data(**scope and linkage**)

## 1.1 storage duration
c++ uses thress separate schemes (four under c++11) for storing data, and the schemes differ in how long they preserve data in memory. more concrete, A variable’s duration determines when it is created and destroyed.

* 1 **Automatoc storage duration** --- variables declared inside a function definition (include function parameters) have automatic storage duration.   they are created when program execution enters the function or block in which they are defined, and the memory used for them is freed when execution leaves the funtion or block.

* 2 **Static storage duration** --- variables defined outside a function definition or else by the keyword static have static storage duration. they persist for the entire time a program is running.

* 3 **Dynamic storage duration** --- memory allocated by the *new* operator persists until it is freed with the *delete* operator or until the program ends, whichever comes first. this memory has dynatic storage duration and sometimes is termed the free store or the heap.

## 1.2  scope and linkage
*Scope* describes how widely visible a name is in a file(translation unit). for example, a variable defined in a function can be used in that function but not in another, whereas a variable defined in a file above the function can be used in all the function.

*linkage* describes how a name can be shared in different units. A name with *external linkage* can be shared across files, and a name with *internal linkage* can be shared by functions within a single file.


A c++ variable can have one of several scopes.

(1) A variable that has *local scope*(also termed block scope) is known only withn the block in which it is defined. a function body, for example, is a block, but you can have other other blocks nested with the function body.

> Recall that a block is a series of statments exclosed in brace.

(2) A variable that has *global scope*(also termed file scope) is known throughout the file after the point where it is defined.

~~~
#include <iostream>

int global_variable = 100;    // global scope

int main()
{
    using namespace std;
    int kk = 22;         // local scope
    cout << "you can access variable with global scope any where: " << global_variable << endl;
    int output = func(kk);  //
    cout << "that value of output = " << output << endl;
    cout << "the kk value is  = " << kk << endl;
    
}

int func(int a)
{
    int count = 2;     // local scope
    a = a + count;         
    return a
}
~~~

# 2 attributes of variable with automatic storage duration

Function parameters and variables declared inside a function have, by default, automatic storage duration. they also have local scope and no linkage.

~~~
int main()
{
    int teledeli = 5;            // teledeli allocated and local scope begin
    {
        cout << "Hello\n";
        int websight = -2;        // websight allocated and local scope begin
        cout << websight << ' ' << teledeli << endl;
    }                             // websight expires
    ...
}                                 // teledeli expires
~~~

# 3 attributes of variable with static storage duration

c++ provides static storage duration variable with three kinds of linkage: extenal linkage(accessible across file), internal linkage(accessible to function within a single file) and no linkage(accessible to just one function or to one block within a function).

> the compiler allocateds a fixed block of memory to hold all the static variable, and thoes variables stay present as long as the program executes.

## 3.1  how to create static storage duration variable
* to create a static duration with external linkage, you declare it outside any block;
* to craete a static duration with internal linkage, you declare if outside any block and use the *static* storage class modifier.
* to create a static duration variable with no linkage, you declared it inside a block, using the *static* modifier.

~~~
...
int global_variable = 1000;  //static duration, global scope, external linkage
                             // is equivalent to    extern int global_variable =  1000;
static int one_file = 50;    //static duration, global scope, internal linkage

void function1(int n)
{
    static int cout = 0;     // static duration, local scope, no linkage
    int lama = 0;
}
~~~


## 3.2 how to use static variable with different linkage

### 3.2.1  static variable with external linkage usage
variables with external linkage, static storage and cross-file scope, can be used in any fcuntion that floows the external variable's definition in the file. oftern simply called external variables or global variables.

**one definition rule**
oe the one hand, an external variable has to be declared in each file that uses the variable. on the other hand, c++ has the "one definition rule", which states that there can be only one definition of a variable. to satisfy these requirements, c++ introduces two kinds of *declaration*:

* defining declaration: it causes storage for the variable to be allocated.
* referecing declaration: it doesn't cause storage to be allocated because it refers to an existing variable.

~~~
// file01.cpp
int fleas;               // (definition) declaration
int dogs = 22;           // definition declaration because of initilization
extern int cats = 20;    // definition declaration
...                      // **all of them are static variables with external linkage**
~~~ 

~~~
// file02.cpp
// use cats and dogs from file01.cpp
extern int cats;          // referencing declaration because they already exist
extern int dogs;          // referencing declaration
~~~

~~~
// file03.cpp
extern int cats;
extern int dogs;
extern int fleas;        // all of them are deferencing declaration
~~~

### 3.2.2 static variable with internal linkage
apply sttic modifier to a file-scope variable gives it internal linkage, all are syntax.
the difference between internal linkage and external linkage becomes meainingful in multifile programs. in that context, a variable with internal linkage is local to the file that containsi it.

~~~
// file1.cpp
int errors = 20;      // external declaration
...
~~~

~~~
// file2.cpp
static int errors = 5;      // known to file2.cpp only
void froobish()
{
    cout << errors;    //use errors defined in files.cpp
}
~~~

### 3.2.3 static variable with no linkage
create a variable by applying the *static* modifier to a variable defined inside a block. when you use it inside a block, *static* causes a local variable to have static storage duration.

~~~
void function1(int a)
{
    static int total = 0;               // static local variable
    int cout = 0;                       // automatic local variable
}
~~~

# 4 the attribute of variable with dynamic storage duration

variable with dynamic storage duration, created by *new* operators, not ny scope and linkage rules.



# 5 appendix

## 5.1 function and it's linkage
like variable, functions have linkage properties, although the selection is mote limited tha for variables.

c++ does not allow you to define one function inside another, so all functions automatically have static storage duration, meaning that they are all present as long as the program is running.

(1) similar to variabel, by default, functions have external linkage, meaning they can be shared across file, cross-file scope.  you can, in fact, use the keuword *extern* in a funtion prototype to indicate that the function is defined in another file. but that is optional.
~~~
void func1(int n)
{
   ...
}

extern void func2(int n)
{
    ...
}

static void func3(int n)
{
    ...
}
~~~

## summary

### a-Scope summary

> An identifier’s scope determines where the identifier can be accessed within the source code.

Variables with block scope / local scope can only be accessed within the block in which they are declared (including nested blocks). This includes:
* Local variables
* Function parameters
* User-defined type definitions (such as enums and classes) declared inside a block
* Variables and functions with global scope / file scope can be accessed from the point of declaration until the end of the file. This includes:
* Global variables
* Functions
* User-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope

### b-Duration summary
> A variable’s duration determines when it is created and destroyed.

* Variables with automatic duration are created at the point of definition, and destroyed when the block they are part of is exited. This includes:
1. Local variables
2. Function parameters
* Variables with static duration are created when the program begins and destroyed when the program ends. This includes:
1. Global variables
2. Static local variables
* Variables with dynamic duration are created and destroyed by programmer request. This includes:
1. Dynamically allocated variables

### c Linkage summary

An identifier’s linkage determines whether multiple declarations of an identifier refer to the same identifier or not.

* An identifier with no linkage means the identifier only refers to itself. This includes:
1. Local variables
2. User-defined type definitions (such as enums and classes) declared inside a block

* An identifier with internal linkage can be accessed anywhere within the file it is declared. This includes:
1. Static global variables (initialized or uninitialized)
2. Static functions
3. Const global variables
4. Functions declared inside an unnamed namespace
5. User-defined type definitions (such as enums and classes) declared inside an unnamed namespace

* An identifier with external linkage can be accessed anywhere within the file it is declared, or other files (via a forward declaration). This includes:
1. Functions
2. Non-const global variables (initialized or uninitialized)
3. Extern const global variables
4. Inline const global variables
5. User-defined type definitions (such as enums and classes) declared inside a namespace or in the global scope

Identifiers with external linkage will generally cause a duplicate definition linker error if the definitions are compiled into more than one .cpp file (due to violating the one-definition rule). There are some exceptions to this rule (for types, templates, and inline functions and variables) -- we’ll cover these further in future lessons when we talk about those topics.

> Also note that functions have external linkage by default. They can be made internal by using the static keyword.


Because variables have scope, duration, and linkage, let’s summarize in a chart:

|Type	   |Example	|Scope |	Duration   |	Linkage	|Notes     |
|----------|--------|------|------------|------------|----------|
|Local variable|int x;|	Block|	Automatic|	None|-	|
|Static local variable|	static int s_x;|	Block|	Static|	None| - |
|Dynamic variable|	int *x { new int{} };|	Block|	Dynamic|	None|-|	
|Function parameter|	void foo(int x)	|Block|	Automatic|	None|-|	
|External non-constant global variable|	int g_x;|	File|	Static|	External|	Initialized or uninitialized|
|Internal non-constant global variable|	static int g_x;|	File|	Static|	Internal|	Initialized or uninitialized|
|Internal constant global variable|	constexpr int g_x { 1 };|	File|	Static|	Internal|	Must be initialized|
|External constant global variable|	extern constexpr int g_x { 1 };|	File|	Static|	External|	Must be initialized|
|Inline constant global variable |	inline constexpr int g_x { 1 };|	File|	Static|	External|	Must be initialized|
|Internal constant global variable|	const int g_x { 1 };|	File|	Static|	Internal|	Must be initialized|
|External constant global variable|	extern const int g_x { 1 };|	File|	Static|	External|	Must be initialized at definition|
|Inline constant global variable|	inline const int g_x { 1 };|	File|	Static|	External|	Must be initialized|
