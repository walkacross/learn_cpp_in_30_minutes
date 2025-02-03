# 1 Function basics

to use a c++ funtion, you must do the followng:
* provide a function definition
* provide a function prototype
* call the funtion

one concrete example you can understanding this
~~~
#include <iostream>

// function declaration
double cube(double x); // function prototype, tell the compiler function info

//function definition
double cude(double x)
{
    return x * x * x;
}

// function call
int main()
{
    using namespace std;
    double side = 5;
    double volume = cude(side); // call function
    cout << "after cude, the value is " << volume << endl;
    return 0;
}
~~~

## 1.1 what and why function declaration or prototype
A funtion declaration or prototype describe the function interface tot the compiler. That is, it tells the compiler what type of return value, if any, the function has, and it tells the compiler the number and type of function arguments.

## 1.2 the general form of function definition

~~~
typeName functionName(parameterList)
{
    statements
    return value;  // value is type cast to the type typeName
}
~~~

## 1.3 function arguments and passing by value
It's time to take a closer look at function argument and c++ normally passes arguments by value. let's look into the process.

~~~
// function definition
double cude(double x)    // a variable that is used to receive passed values is called a formal argument.

// when call function
double side = 5;
double olume = cude(side);  // the numerc value of the argument is passed to the function. the value passed to a function is called actual argument.
~~~

what really happens when pass a actual argument to a function?
when this function is called, it create a new type double variable called x and initialize it with the value 5. something like do a omiited assignment statement

~~~
double x = side; 
~~~ 
