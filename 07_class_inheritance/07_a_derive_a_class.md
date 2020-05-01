# 1 Beginning with a simple base class
when one class inherits from another, the original class is called *a base class*, and the inheriting class is called *a detived class*. to illustrate inheritance, let's begin with a base class.

all technique in c++ is two rules

rule1: everything is an object, the object has many attributes to set.
rule2: the related operatios of an object has three: (1) object declaration; (2)object definition; (3) object usage.


~~~
// tabtenn0.h -- a table-tennis base class
#ifndef TABLETENN0_H_
#define TABLETENN0_H_

#include <string>
using std::string

// simple base class
class Animal
{
private:
    string firstname;
    string lastname;
    bool hasTable;


protected:
    double balance;


public:
    Animal (const string & fn = 'none', const string & ln = "none", bool ht = false);
    void Name() const;
    bool HasTable() const {return hasTable;};
    void ResetTable(bool v) { hasTable = v;};
}
~~~
see that, a class actually has three type of attributes according its access control. we will describe the detail later.



# 2 deriving a class
if somewhere you need create a Dog class and you find that the attributes of Animal is subset of the attributes of Dog. so ranther than define a class from scrach, you can derive a class from the Animal class.  the class declaration is following:
~~~
class DogAnimal : public Animal
{
...
}

this particular heading indicates that Animal is a public base class, this is termed public derivation. with public derivation:

1 the public/protected mmebers of the base clas become public/protected members of the derived class.

2 the private portion of a base class become part of the derived class, but they can be access only through public and protected method of the base class.


what needs to be added to these inherited feature？
* a derived class needs its own constructors.
* a derived class can add additional data members and members functions as needed.
~~~

## 2.1 subclass declaration
~~~
// simple derived class
class DogAnimal : public Animal
{
private:
    unsigned int rating;    //add a data member

public:
    DogAnimal (unsigned int r = 0, const string & fn = "none", const string & ln = "non", bool ht = false);
    DogAnimal (unsigned int r, const Animal & tp);
    unsigned int Rating() const {return rating;}    // add a method
    void ResetRating (unsigned int r) {rating = r}  // add a method
};
~~~

A derived class does not have direct access to the private members of the base class; it has to work through the base-clas methods. for example, the DogAnimal constructors cannot directly set the inherited members(firstname...), instead, they have to use publich base-class methods to access private base-class members.

## 2.2 subclass definition
~~~
DogAnimal::DogAnimal(unsigned int r, const string & fn,
                     const string & ln, bool ht) : Animal(fn,ln,ht)
{
    rating = r;
}
~~~
note: the base-class object must be created first.


## 2.3 subclass usage

to use a derived class, aprogram needs access to the base-class declarations.

~~~
// animal1.h 
#ifndef ANIMAL0_H_
#define ANIMAL0_H_

#include <string>
using std::string;

class Animal
{
private:
    string firstname;
    string lastname;
    bool hasTable;

protected:
    double balance;

public:
    Animal(const string & fn = "none",
           const string & ln = "none",
           bool ht = false);

    void Name() const;
    bool HasTable() const {return hasTable;};
    void ResetTable(bool v){hasTable=v;};
};

// simpole derived class

class DogAnimal : public Animal
{
private:
    unsigned int rating;

public:
    DogAnimal (unsigned int r = 0, const string & fn = "none",
               const string & ln = "none", bool ht = false);
    DogAnimal (unsigned int r, const Animal & tp);
    unsigned int Rating() const {return rating;}
    void ResetRating (unsigned int r) {rating  = r;}
};

#endif
~~~


~~~
// animal1.cpp
#include <iostream>
#include "animal1.h"
using std::string

Animal::Animal (const string& fn, const string& ln, bool ht)
{
    firstname = fn;
    lastname = ln;
    hasTable = ht;
}

void Animal::Name() const
{
    std::cout << lastname << ", " << firstname;
}


//
DogAnimal::DogAnimal(unsigned int r, const string& fn,
       const string& ln, bool ht) : Animal(fn,ln,ht)
{
    rating = r;
}

DogAnimal::Doganimal(unsinged int r, const Animal& tp) : Animal(tp)
{
    rating = r;
}
~~~


**use test**

~~~
// usetest1.cpp
#include <iostream>
#include "animal1.h"

int main(void)
{
    using std::cout;
    using std::endl;
    Animal animal1("tara", 'bob', false);
    DogAnimal danimal1(222, 'mary', 'duck', true);
    

    animal1.Name();            //base use base method
    danimal1.Name();           // derived object uses base method
    danimal1.Rating();         // detived object uses own method


    DogAnimal danimal2(1212, animal1);   //another constructor
    danimal2.Name();

    return 0;
}
~~~


conclusion:

(1) a derived class obejct can use base-class methods, provided that the methods are not private:

(2) a base-class pointer can point to a derived-class object without an explicit type cast and that a base-class rederence can refer to a derived-class object without an explicited type case:
~~~
DogAnimal danimal1(1211, 'kk','dd', true);
Animal & rt = danimal1;
Animal * pt = &danimal1;
rt.Name();
pt->Name();   // invode Name() with pointer
~~~
however, a based-class pointer or rederence can invoke just base-class methods.




# Appendix

the protected keywords is like private in that the ouside world can access class members in a protected section *only by using public class members*. the differenece is : memebers of a derived class can access protected members of a base class directly, but they cannot directly access private members of the base class.






