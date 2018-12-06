# 1 class and instance

> class is a set of things having some property or attribute in common: like animal,it's a set none.》 i

> instance(object) is a concrete example or single occurrence pf something belong to a class.


in computer, every is a object. 2 is an instance, which belong to *int* class, 12.34 is an instance, which belong to "double" class.

how to define a user-defined type (or class) in c++ ?  recall that a class is a set of things having some attribute in common. in practice, what we usually do is: observe many objects and its attributes, and abstract a set of things having common attribute into a class. after that, we can generate many objects by that class.


a class specification in c++ has two part:

* a class declaration, which describes the atributes that class have. particarlly, member variables and member functions, termed methods

* the class method definition. which describe how certain class member functions are implemented.


> generally, a class has many attributes. according to it's access control, they can be catogary into three: public, private, protect.


# 2 class declaration

~~~
// stock00.h -- stock class
// version 0.1

#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>

class Stock              // class declaration
{
private:
    std::string company_name;
    long shares;
    double share_val;
    double total_val;
    void set_tot(){ total_val = shares * shares_val;}

public:
    void acquire(const std::string & co, long n, double pr);
    void buy(long num, double price);
    void update(double price);
    void show();
};                        // note semicolon at the end

#endif
~~~

# 3 class definition -- implementing class member functions

member function definition in a class are much lile regular function definition, but they also have two special characteristics:

* when you define a member function, you use the scope-resolution operator(::) to identify the class to  which the function belong.
* class methods can access the private attributes of the class.

~~~
// stock00.cpp  -- class definition
// version 00

#include <iostream>
#include "stock00.h"

void Stock::acquire(const std::string & co, long n, double pr)
{
    company_name = co;
    if (n < 0)
    {
        std::cout << "number can't be negative"
        shares = 0;
    }
    else
        shares = n;
        share_val = pr;
        set_tot();
}


void Stock::buy(long num, double price)
{
    if (num < 0)
    {
        std::cout << "number to purchased can not be negative";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    int local_var = 0.1
    share_val = price + local_var;
    set_tot();
}

void Stock::show()
{
    std::cout << "company name :" << company_name
              << " shares: " << shares << "\n"
              << " shares price: $" << share_val
              << " total worth: $" << total_val << "\n";   
}
~~~

# 4 use class

~~~
// use stock00.cpp -- the client program
#include <iostream>
#include "stock00.h"

int main()
{
    Stock fluffy_the_cat;
    fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
    fluffy_the_cat.show();
    fluffy_the_cat.buy(12, 18.96);
    fluffy_the_cat.show();
    return 0;
}
~~~
