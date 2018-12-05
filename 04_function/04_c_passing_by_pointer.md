# 1 what is a pointer

A pointer is a special type of data object, whoes value attribute holds a memory address. and you can use * operator, called the dereference operator, yields the valueat that location.

## 1.1 how to create a pointer
**declaration statement**
~~~
int* pt;  // declare pointer to an int
~~~

**assignment statement**
~~~
int higgens = 5;
pt = &higgens
~~~

or you can combine these into one:
~~~
int higgens = 5;
int* pt = &higgens
~~~

## 1.2 how to use the pointer -- dereferencing pointer
~~~
#include <iostream>

int main()
{
    using namespace std;
    int updates = 6;
    int* p_updates;        //declare pointer to an int
    p_updates = &updates;  // assign address of int to pointer

    //express values in two ways
    cout << "values updates = " << updates;
    cout << ", *p_updates = " << *p_updates << endl;

    //express address in two ways
    cout << "address &updates = " << &updates;
    cout << ", p_updates = " << p_updates << endl;

    // use pointer to change value(important)
    *p_updates = *p_updates + 1;
    cout << "now the value of updates  = " << updates << endl;    // display 7
    return 0;
}
~~~

## 1.3 allocateing memory with new
so far, you have initialized pointers to the address of variable which are named emory allocated during compile time. and each pointer merely provides an alias for memory you could access directly by name anyway.


The truth worth of pointers comes into play when you allocate unnamed memory during runtime to hold values. In this case, pointers become the only access to that memory.

let try out this new technique by creteing unnamed runtime storage for a type int value and accessing the value with a pointer.
~~~
int* pn = new int;
*pn = 101;
~~~
because the memory to which pn points lacks a name, what do you call it?
we say that pn points to a data object, you can access that data object only by this pointer.  the pointer method for handling data objects may seem more awkward at first, but it offers greater control over how you program manages memory.

the general for  for obtaining and assigning memory for a single data object, which can be a structure as well as a fundamental type is this:
~~~
typeName * pointer_name = new typeName;
~~~

## 1.4 freeing memory with delete
using new to request ,e,ory is the half of the c++ memory management package, the other half is the delete operator, which enables you to return memory the memory pool when you are finished with it.

~~~
int * ps = new int;      // allocate memory with new
...                      // use the memory
delete ps;               // free memory with delete when done
~~~

**note** this only removes the memory to which ps point; it doesn't remove the pointer ps itself. you can reuse ps. for example, to point to another new allocation.

you should always balance a use of *new* with a use of *delete*, otherwise, you can wind up with a **memory leak**. that is, memory that has been allocated but can no longer be used. if a memory leak grows to large, it can bring a program seekin more memory to a halt.


# 2 passing by pointer to a function
as mention in 04_b, there are three ways to passing argument; passing by value, passing by reference, passing by pointer. here we will continue to talk about the passing by pointer.

~~~
#include <iostream>

//function declaration
void swapp(int * p, int * q);   // p, q are addresses of ints

int main()
{
    using namespace std;
    int wallet1 = 300;
    int wallet2 = 350;

    cout << "using pointers to swap contents:\n";
    swapp(&wallet1, &wallet2);   // pass addresses of variables
    cout << "wallet1 = $" << wallet1;
    cout << "wallet2 = $" << wallet2 << endl;
    
    return 0;
}

// funtion definition
void swapp(int * p,int * q)   // use pointer as argument
{
    int temp;
    
    temp = *p;    // dereference pointer
    *p = *q;      // dereference and then assignment to that data object
    *q = temp;
}
~~~

