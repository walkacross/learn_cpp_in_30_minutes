# 1 namespace
> https://docs.microsoft.com/en-us/cpp/cpp/namespaces-cpp

names in c++ can refer to variables, function, structures, enumerations, classes, and class and struct members.  when programming projects grow large, the potential for name conflics increses, such conflics are termed *namespace problem*. the c++ standard provides namespace facilities to provide greater control over the scope of names.


## 1.1 traditonal c++ namespaces
one term you need to be aware of is *declarative region*. a declarative region is a region in which declarations can be made.
    * you declare a global variable outside any function. the declarative region for that variable is the file in which it is declared.
    * if you declare a variable inside a function, its declarative region is the innermost block in which it is declared.

a second term you need to aware of is *potential scope*: the potential scope for a variable begins at its point of declaration and extends to the end of its declarative region.

however, a variable might not be visible everwhere in its potential scope. for instance, it might be hidden by another variable of the same name declared in a nested declarative region.

## 1.2new namespace feature
c++ now adds the ability to create named namespaces by defineing a new kind of declarative region. one whoes main purpose is to provide an area in which to declare names. the names in one namespace don't conflict with the same names declared in other namespaces. and there are mechanisms for letting other parts of a program use items declared in a namespace.

use the kwyword *namespace* to create two namespaces, *Jack* and "Jill"
~~~
namespace Jack{
    double pail;                 //variable declaration
    void fetch();                //function declaration
    int pal;                     //variable declation
    struct Well{};               //structure declaration
}

namespace Jill{
    double bucket(double n){...}   //function definition
    double fetch;                  
    int pal;
    struct Hill{...};
}
~~~

## 1.3 namespace are open
(1) if namespace provide a claration, you can provide the definition code for the declaration later in the file or in another file by using the namespace again:
~~~
namespace Jack{
    void fetch()
    {
     ...
    }
}

(2) you can add names to existing namespaces.
namespace Jill{
    char * goose(char*);
}

## 1.4 how to access names in a given namespace.
the simplest wau is to use ::, the scope-resolution operator, to *qualify* a name with its namespace:
~~~
Jack::pail = 12.34;          // use a variable
Jill::Hill mole;             // create a type Hill structure
Jack::fetch();               // use a function
~~~

## 1.5 using declarations versus using directives
~~~
using Jill::fetch;      // a using declaration
using namespace Jill    // using rirectives
~~~
A using declaration, then, make a single name available. In contrast, the using derective makes all the names available.

## 1.6 more namespace feature

### 1.6.1 namespace nest
you can nest namespace declarations, like this:

namespace elements
{
    namespace fire
    {
        int flame;
    }

    float water;
}

in this case, you refer to the flame variable as elemetns::fire::flame. similarly, you can make the inner names available with this using directive
~~~
using namespace elements::fire
~~~

## 1.6.2
also you can using directive and using decllarations inside namespaces. like this
~~~
namespace myth
{
    using Jill::fetch;
    using namespace elements;
    using std::cout;
    using std::cin;
}
~~~

the way you can access
~~~
myth::fetch;
Jill::fetch;
~~~

## 1.7 concrete example about namespaces
