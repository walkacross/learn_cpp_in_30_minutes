# 1 why use header file?

the general case, you declare a funtion prototype and define it in one file. this function, by default, is a external linkage function, that means other file can use this function, but they have to referencing decalratin in their file.  think about his situition, when three file want to use this funtion, you have to refernecing declaration three times.  how to avoid this case?

the solution:
step 1: place the function decalration and definition in a separate file. which can be called header file and source code file.

step 2: c++ provide the *#include*  command, which can import the object in header file to source code file.

# 2 what should place to header file.
you shouldn't put function definition or variable declarations into a header file. here are some things commonly found in header files:

* (1) symbolic constants define using #define or const
* (2) function declaration
* (3) struct declaration
* (4) class declaration
* (5) template declaration
* (6) inline function

# 3 header file management

## 3.1 avoid multiple inclusions of header files
you should include a header file just once in a file. there is a standard c++ technique for achieve based on the preprocessor #ifndef(for if not define) directive.   a code segment like the following means "process the statements between the #ifndef and #endif only the name COORDIN_H_ has not been defined previously by the preprocessor #define directive"

in header file
~~~
// coordin.h
#ifndef COORDIN_H_
#def COORDIN_H_
// place include file contents here

#endif
~~~

## 3.2 use #define
normally, you use the #define statement to create symbolic constants, as in the following:
~~~
#define MAXIMUM 4096
~~~

## 3.3 concrete example

in header file
~~~
// coordin.h
#ifndef COORDIN_H_
#define COORDIN_H_

// function declaration
void swapr(int& p, int& q);

#endif
~~~

in source code file
~~~
// file1.cpp
#include <iostream>
#include "coordin.h"

void swapr(int& p, int& q)
{
    int temp;
    temp = p;
    p = q;
    q = temp;
}
~~~

in other file
~~~
// file2.cpp
#include <iostream>
#include "coordin.h"

using namespace std;

int main()
{
    int wallet1 = 100;
    int wallet2 = 200;
    swapr(walllet1, wallet2);
    return 0;
}
~~~

