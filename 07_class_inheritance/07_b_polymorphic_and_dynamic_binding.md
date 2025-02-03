# 1 Polymorphc

you can encounter situations in which you want a method to behave differnently for the derived class than it does for the base class. that is, the way a particular method behaves may depend on the object that invokes it. this more sophisticaed behave is termed *polymorphic*.

there are two key mechanisms for implemmenting polymorphic public inherithance.

1 redefining base-class methods in a derived class
2 using virtual member methods

## 1.1 redefine base-class methods in a derived class

~~~
// brass.h  -- bank account classes
#ifndef BRASS_H_
#define BRASS_H_

// Brass Account class
class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;

public:
    Brass(const std::string & s = 'Nullbody', long an=-1,double al=0.0);
    void Deposit(double amt);
    void Withdraw(double amt);
}

class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;
public:
    BrassPlus(const std::string & s = 'Nullbody, long an = -1, double bal=0.0,
              double ml = 500, double r = 0.1123);
    BrassPlus(const Brass & ba, double ml=500, double r = 0.1123);
    void Withdraw(double amt);
    void ResetRate(double r) {rate = r;};
};

#endif
~~~

how to use redefine?
~~~
Brass dom("Dominic Banker", 11223, 4123.45);
BrassPlus dot("Dorothy", 12118, 2592.00);

dom.withdraw(11);      // use Brass::Withdraw()
dot.withdraw(11);      // use BrassPlus::Withdraw()
~~~

but the shortpoint here is:
~~~
Brass & b1_ref = dom;
Brass & b2_ref = dot;

b1_ref.Withdraw(11);  // use Brass::Withdraw()
b2_ref.Withdraw(11);  // still use Brass::Withdraw()

the reference variable are type Brass, so call the Brass::Withdraw() is chosen.
using pointers to Brass instead of reference reult in similar behavior.
~~~

## 1.2 use virtual member function
~~~
// brass.h -- bank account class
#ifndef BRASS_H_
#define BRASS_H_

#include <string>

class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;

public:
    Brass(const std::string & s = 'Nullbody', long an =-1, double bal=0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt);
    virtual ~Brass(){}
};

//Brass Plus account class
class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;

public:
    BrassPlus(const std::string & s = 'Nullbody', long an=-1, double bal=0.0,
              double ml=500, double r=0.1123);
    BrassPlus(const Brass & ba, double ml = 500, double r = 0.1123);
    virtual void Withdraw(double amt);
    void ResetRate(double r) {rate = r;};
};

#endif
~~~


class definition
~~~
// brass.cpp
#include <iostream>
#include "brass.h"

using std::cout;
using std::endl;
using std::string;

//
Brass::Brass(const string & s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void Brass::Deposit(double amt)
{
    if (amt < 0)
        cout << "negative deposit not allowed";
    else
        balance += amt;
}

void Brass::withdraw(double amt)
{
    if (amt < 0)
        cout << "withdraw amotunt must be positive";
    else if (amt <= balance)
        balance -= mat;
    else
        cout << "excess you amount";
}

BrassPlus::BrassPlus(const string & s, long an, double bal,
                     double ml, double r) : Brass(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : Brass(ba) // copy
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

// implement virtual function
void BrassPlus::Withdraw(double amt)
{
    if (amt <= bal)
        Brass::Withdraw(amt);   // can call parent same name method
    else if ( amt <= bal + maxLoan - owesBank)
    {
        doubke advance = amt - bal;
        owesBank += advance * (1.0 + rate);
        Deposit(advance);
        Brass::Withdraw(amt);
    }
    else
        cout << "credit limit exceed";
}
~~~

how to use it?

~~~
BrassPlus ophelia;
Brass * bp;
bp = &ophelia;   // Brass pointer to BrassPlus object
bp -> Withdraw(11);  // which version?
~~~

conslusion:
* if Withdraw() is not declared as virtual in the base class, bp -> Withdraw() goes by the pointer type (Brass *) and invoke Brass::Withdraw().

* if Withdraw() is declared as virtual in the base class, bp->Withdraw() goes by the object type (BrassPlus) and invokes BrassPlus::Withdraw().


# 2 Appendix notes

## 2.1 how virtual methods at work?  -- static and dynamic binds
which block of executable code gets used when a program calls a function? the compiler has the responsibility of answering this question.

interpreting a function call in the source code as executing a particular block of funtion code is termed *binding the function name*.

with c++, the task is more complex because of function overloading. the complier has to look at the function arguments as well as the function name to figure out which function to use. Nonetheless, this kind of binding is a task a c++ compilier could perfom during the cmpiling process; 
> binding that takes place during complilation is called static binding.

however, virtual functions make the job more diffcul yet. the decsion of which function to use can't be made at compile tie, because the compilier doesn't know which kind of object the user is going to choose to make. therefore, the compilier has to generate code that allows the correct virtual method to be selected as the programruns, this is called *dynamic binding*.

* in short, the compilier use staic binding for non-virtual methods, the compilier uses dynamic binding for virtual methods.

* dunamic binding in c++ is associated with methods invoked by pointers and references and this is governed, in part, by the inheritance process.

* converting a derived-class reference or pointer to ba base-class reference or pointer is called *upcasting*, and it is always allowed for pulic inheritance without the nedd for an explicit type cast.
~~~
BrassPlus dilly(("Anniew DILL",45343,2000);
Brass * pb = &dilly;   // ok
Brass & rb = dilly;    // ok
~~~

* the need for virtual destructors. if the destructor are virtual, the destructor corresponding tot he object type is called.

## 2.2 why two kinds of binding and why static is the default

there are two reasons: efficiency and a conceptual model.

1 for a program to be able to make a runtime decision, it has to have some way to keep track of what sort of object a base-class pointer or reference reders to, and that entails some extra processing overhead. the fact that static binds is more efficient is the reason it is the default choice for c++.

2 let consider the conceptual model. when you desifn a class, you may have member funtions that you don't wnat redefined in derived classes. non-virtual function tell other don't redefine in derived class. virtual tell other to redefine it in derived class.
