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

# passing by a reference to function

passing by reference allows a clled function to access variables in the calling function. which results from the shadow copy.

~~~
// swaps.cpp
#include <iostream>

void swapv(int a, int b);  // passing by value
void swapr(int& a, int& b); // passing by reference

int main()
{
    using namespace std;
    int wallet1 = 300;
    int wallet2 = 350;
    cout << "wallet1 = $" << wallet1;
    cout << "wallet2 = $" << wallet2;

    cout << "trying to passing by value...";
    swapv(wallet1, wallet2);            // passing by value
    cout << "wallet1 = $" << wallet1;   // display 300
    cout << "wallet2 = $" << wallet2:   // display 350. failed swap

    cout << "passing by reference";
    swapr(wallet1, wallet2);
    cout << "wallet1 = $" << wallet1;   // display 350
    cout << "wallet2 = $" << wallet2;   // display 300 success swap
    return 0;
}

void swapr(int a, int b)
{
    int temp;
  
    temp = a;
    a = b;
    b = temp;
}

void swapr(int& a, int& b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;
}
~~~
when passing a actual argument to function, the function will do an omitted step. create a reference by assignment:
~~~
int& a = wallet1;
int& b = wallet2;
~~~
after creating
~~~
a = b; //this assignment statement actually. assign the value of object b to the value attribute of object a. thereby alter the wallet1's value attribute.
~~~

