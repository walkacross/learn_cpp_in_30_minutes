# Abstract Base Class
In some situation, you need to create a base class which others can't create an object of that class.   how to achieve this in c++?

you just declare a pure virtual function in a base class. the idea is that classes with pure virtual functions exist solely to serve as base classes.
> it is the =0 in the prototype taht make a virtual function a pure virtual function.

~~~
//acctable.h

#ifndef ACCTABC_H_
#define ACCTABC_H_

#include <iostream>
#include <string>

//Abstract Base Class
class AcctABC
{
private:
    std::string fullName;
    long acctNum;
    double balance;

protected:
    const std::string & FullName() const {return fullName;}
    long AcctNum() const {return acctNum;}
 
public:
    AcctABC(const std::string & s = 'Nullbody', long an = -1, double bal=0.0);
    void Deposit(double amt);
    virtual void Withdraw(double amt) = 0; // pure virtual function
    double Balance() const {return balance;}
    virtual void ViewAcct() const = 0;    //pure virtual function
    virtual ~AcctABC(){}
};

// Brass Account Class
class Brass : public AcctABC
{
public:
    Brass(const std::string & s = "Nullbody", long an = -1, 
          double bal=0.0) : AcctABC(s,an,bal){}
    virtual void Withdraw(double amt);
    virtual void ViewAcct() const;
    virtual ~Brass(){}
};

// Brass Plus Account Class
class BrassPlus : public AcctABC
{
private:
    double maxLoan;
    double rate;
    double owesBank;

public:
    BrassPlus(const std::string & s = 'Nullbody', long an = -1,double bal=0.0,
              double ml=500, double r = 0.01);
    BrassPlus(const Brass & ba, double ml=500, double r = 0.1);
    virtual void ViewAcct() const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) {maxLoan = m;}
    void ResetRate(double r) {rate = r;}
    void ResetOwes() {owesBank = 0;}
};

#endif
~~~

the next step is to implement the methods that don't already have inline definition.

~~~
// acctabc.cpp

#include <iostream>
#include "acctabc.h"
using std::cout;
using std::endl;
using std::string;

//Abstract Base Class
AcctABC::AcctABC(const string & s, long an, double bal)
{
    fullName = s;
    acctNum = an;
    balance = bal;
}

void AcctABC::Deposite(double amt)
{
    if (amt < 0)
        cout << "no negative";
    else
        balance += amt;
}

// 
void AcctABC::Withdraw(double amt)
{
    balance -= amt;
}

// Brass methods
void Brass::Withdraw(double amt)
{
    if (amt < 0)
        cout << "plz no negative";
    else if (amt <= Balance())
        AcctABC::Withdraw(amt);
    else
        cout <<  "exceed your balance";
}

void Brasss::ViewAcct() const
{
    cout << "name " << FullName() << endl;
    cout << "balance " << Balance() << endl;
}

// BrassPlus Method
BrassPlus::BrassPlus(const string & s, long an, double bal,
                     double ml, double r) : AcctABC(s, an, bal)
{
    maxLoan = ml;
    owesBank = 0.0;
    rate = r;
}

void BrassPlus::ViewAcct() const
{
    cout << "BrassPlus client: " << FullName() << endl;
}

void BrassPlus::Withdraw(double amt)
{
    double bal = Balance();
    if (amt <= bal)
        AcctABC::Withdraw(amt);
    else if (amt <= bal + maxLoan - owesBank)
    {
        double advance = amt - bal;
        owesBank += advance * (1.0 + rate);
        Deposit(advance);
        AcctABC::Withdraw(amt);
    }
    else
        cout << "credit limit exceeded.";
}
~~~


## experience
* every variable, function, methods in class can be used only after declaration and definition. for class methods, you can inline define it in header file, or you define in source file.

* every variable, function, memethos in class are object, object should be with some attributes, like name, type, name, value, address, duration, scope,linkage, const, or virtual or pure virtual. you can set some attributes to it by c++ keyword, and the object will behave differently according its attributes.


