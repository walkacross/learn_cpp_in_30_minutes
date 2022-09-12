# seperation of header and source file.
[C++ Header File Guidelines](http://websites.umich.edu/~eecs381/handouts/CppHeaderFileGuidelines.pdf)

[what happends if Writing function definition in header files in C++](https://www.techtalk7.com/writing-function-definition-in-header-files-in-c/)


# How to tell g++ compiler where to search for include files?

In Python, you import modules, and the equivalent in C++ is a #include (pound include). There are two different ways to use this statement:

* #include <iostream> When using the angle brackets, < and >, this tells the compiler to include libraries that are in pre-defined locations based on the setup for your compiler or IDE (e.g., Qt Creator).

* #include "all-examples.h" When using double quotes, this tells the compiler to first search in the same directory as the current file.

**question**: how to tell the compiler where to search the head file

* method 1: add relative path
~~~
/test1/one/main.h

/test1/one/main.cpp

/test1/one/good.h

/test1/two/some.h

/test1/two/some.cpp
~~~

~~~
//main.cpp
#include "good.h"
#include "../two/some.h"
~~~

* method 2: add the directory to the environment variable.

in g++
~~~
// tell the compiler search path
g++ -Idir
~~~
[how-to-tell-g-compiler-where-to-search-for-include-files](https://stackoverflow.com/questions/15478005/how-to-tell-g-compiler-where-to-search-for-include-files)

in cmake
~~~
# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(hello_headers
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )
~~~

# Why can templates only be implemented in the header file?

[Why can templates only be implemented in the header file](https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file)

