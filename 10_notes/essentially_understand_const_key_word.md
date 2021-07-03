# essentially understand const keyword in c++

> Constant is something that doesn't change. In C language and C++ we use the keyword const to make program elements constant.

**const** keyword can be used in many contexts in a C++ program. It can be used with:

1.Variables

2.Pointers

3.Function arguments and return types

4.Class Data members

5.Class Member functions

6.Objects

## 1 Constant Variables in C++
If you make any variable as constant, using const keyword, you cannot change its value. Also, the constant variables must be initialized while they are declared.
~~~
#include <iostream>
using namespace std;
 
// Driver Code
int main()
{
 
    // const int x;  CTE error
    // x = 9;   CTE error
    const int y = 10;
    cout << y;
 
    return 0;
}
~~~
Such constants are useful for parameters which are used in the program but do not need to be changed after the program is compiled. It has an advantage for programmers over the C preprocessor ‘#define’ command in that it is understood & used by the compiler itself, not just substituted into the program text by the preprocessor before reaching the main compiler, so error messages are much more helpful.


## 2 Pointers with const keyword in C++

Pointers can be declared using const keyword too. When we use const with pointers, we can do it in two ways, either we can apply const to what the pointer is pointing to, or we can make the pointer itself a constant.

### 2-a When the pointer variable point to a const value:
As evident from the name, a pointer through which one cannot change the value of variable it points is known as a pointer to constant. These type of pointers can change the address they point to but cannot change the value kept at those address by the pointer.

Syntax:
~~~
const data_type* var_name;
~~~

Below is the example to demonstrate the above concept:
~~~
// C++ program to demonstrate the
// above concept
#include <iostream>
using namespace std;

// Driver Code
int main()
{
	int x{ 10 };
	char y{ 'M' };

	const int* i = &x;
	const char* j = &y;

	// Value of x and y can be altered, by the varibale self
	// they are not constant variables
	x = 9;
	y = 'A';

	// Change of constant values because,
	// i and j are pointing to const-int
	// & const-char type value
	// *i = 6; //Error: Since the value is constant, cannot change the value kept at those address by the pointer. 
	// *j = 7; //Error: Since the value is constant, cannot change the value kept at those address by the pointer.

	cout << *i << " " << *j;
}
~~~
output
~~~
9 A
~~~

Explanation: Here in the above case, i and j are two pointer variables that are pointing to a memory location const int-type and char-type, but the value stored at these corresponding locations can be changed as we have done above. 

### 2-b When the const pointer variable point to the value
A constant pointer is a pointer that cannot change the address its holding. In other words, we can say that once a constant pointer points to a variable then it cannot point to any other variable.

Syntax:
~~~
data_type* const var_name;
~~~

Below is the example to demonstrate the above concept:
~~~
// C++ program to demonstrate the
// above concept
#include <iostream>
using namespace std;

// Driver Code
int main()
{
	// x and z non-const var
	int x = 5;
	int z = 6;

	// y and p non-const var
	char y = 'A';
	char p = 'C';

	// const pointer(i) pointing
	// to the var x's location
	int* const i = &x;

	// const pointer(j) pointing
	// to the var y's location
	char* const j = &y;


	// The values that is stored at the memory location can modified
	// even if we modify it through the pointer itself
	// No CTE error
	*i = 10;
	*j = 'D';

	// CTE because pointer variable
	// is const type so the address
	// pointed by the pointer variables
	// can't be changed
	// *i = &z;
	// *j = &p;

	cout << *i << " and " << *j
		<< endl;
	cout << i << " and " << j;

	return 0;
}

~~~


output
~~~
10 and D
0x7ffd1ff8f830 and MC
~~~
Explanation: The values that are stored in the corresponding pointer variable i and j are modifiable, but the locations that are pointed out by const-pointer variables where the corresponding values of x and y are stored aren’t modifiable. 

### 2-c When const pointer pointing to a const variable:

If you have understood the above two types then this one is very easy to understand as its a mixture of the above two types of pointers. A constant pointer to constant is a pointer that can neither change the address its pointing to and nor it can change the value kept at that address by the pointer.

Syntax:
~~~
const data_type* const var_name;
~~~

Below is the C++ program to demonstrate the above concept:
~~~
// C++ program to demonstrate
// the above concept
#include <iostream>
using namespace std;

// Driver code
int main()
{
	int x{ 9 };

	const int* const i = &x;

	// *i=10;
	// The above statement will give CTE
	// Once Ptr(*i) value is
	// assigned, later it can't
	// be modified(Error)

	char y{ 'A' };

	const char* const j = &y;

	// *j='B';
	// The above statement will give CTE
	// Once Ptr(*j) value is
	// assigned, later it can't
	// be modified(Error)

	cout << *i << " and " << *j;

	return 0;
}

~~~

output
~~~
9 and A
~~~

Explanation: Here, the const pointer variable points to the const variable. So, you are neither allowed to change the const pointer variable(*P) nor the value stored at the location pointed by that pointer variable(*P).

### conclusion: how to distinguish?

1. Non-constant pointer to constant data: Data pointed to CANNOT be changed; but pointer CAN be changed to point to another data. For example,
~~~
int i1 = 8, i2 = 9;
const int * iptr = &i1;  // non-constant pointer pointing to constant data
// *iptr = 9;   // error: assignment of read-only location
iptr = &i2;  // okay
~~~

2. Constant pointer to non-constant data: Data pointed to CAN be changed; but pointer CANNOT be changed to point to another data. For example,
~~~
int i1 = 8, i2 = 9;
int * const iptr = &i1;  // constant pointer pointing to non-constant data
                         // constant pointer must be initialized during declaration
*iptr = 9;   // okay
// iptr = &i2;  // error: assignment of read-only variable
~~~

3. Constant pointer to constant data: Data pointed to CANNOT be changed; and pointer CANNOT be changed to point to another data. For example,
~~~
int i1 = 8, i2 = 9;
const int * const iptr = &i1;  // constant pointer pointing to constant data
// *iptr = 9;   // error: assignment of read-only variable
// iptr = &i2;  // error: assignment of read-only variable
~~~
4. Non-constant pointer to non-constant data: Data pointed to CAN be changed; and pointer CAN be changed to point to another data. For example,
~~~
int i1 = 8, i2 = 9;
int * iptr = &i1;  // non-constant pointer pointing to non-constant data
*iptr = 9;   // okay
iptr = &i2;  // okay
~~~
what's the rule to distinguish the object which const point to?

The rule is:

> const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.


You generally read types in C++ from right-to-left, for example Object const * is a pointer to a const Object. If you put the const on the left, it would read as a pointer to an Object that is const,
, which doesn't really flow very well

Read it backwards(read right-to-left) (as driven by Clockwise/Spiral Rule):
~~~
int* - pointer to int
int const * - pointer to const int
int * const - const pointer to int
int const * const - const pointer to const int
~~~
Now the first const can be on either side of the type so:
~~~
const int * == int const *
const int * const == int const * const
~~~

## 3 const Function Arguments and Return types
A function() parameters and return type of function() can be declared as constant. Constant values cannot be changed in function body as any such attempt will generate a compile-time error.
### 3-a: Constant Function Parameters

Below is the C++ program to implement the above approach: 

~~~
// C++ program to demonstrate the
// above approach
#include <iostream>
using namespace std;

// Function foo() with variable
// const int
void foo(const int y)
{
	// y = 6; const value
	// can't be change
	cout << y;
}

// Function foo() with variable int
void foo1(int y)
{
	// Non-const value can be change
	y = 5;
	cout << '\n'
		<< y;
}

// Driver Code
int main()
{
	int x = 9;
	const int z = 10;

	foo(z);
	foo1(x);

	return 0;
}

~~~

output
~~~
10
5
~~~
### 3-b const return type
The return type of the function() is const and so it returns a const integer value to us. 

Below is the C++ program to implement the above approach: 

~~~
// C++ program for the above approach
#include <iostream>
using namespace std;

const int foo(int y)
{
	y--;
	return y;
}

int main()
{
	int x = 9;
	const int z = 10;
	cout << foo(x) << '\n'
		<< foo(z);

	return 0;
}

~~~
output
~~~
8
9
~~~
There is no substantial issue to pass const or non-const variable to the function because the value that will be returned by the function will be constant automatically. As the argument of the function is non-const.

### Some Important points to Remember
1. For built in datatypes, returning a const or non-const value, doesn't make any difference.
~~~
const int h()
{
    return 1;
}

int main()
{
    const int j = h();
    int k = h();
}
//Both j and k will be assigned the value 1. No error will occur.
~~~
2. For user defined datatypes, returning const, will prevent its modification.
3. Temporary objects created while program execution are always of const type.
4. If a function has a non-const parameter, it cannot be passed a const argument while making a call.
5. But, a function which has a const type parameter, can be passed a const type argument as well as a non-const argument.

## 4 Defining Class Data members as const
These are data variables in class which are defined using const keyword. They are not initialized during declaration. Their initialization is done in the constructor.

~~~
class Test
{
    const int i;
    public:
    Test(int x):i(x)
    {
        cout << "\ni value set: " << i;
    }
};

int main()
{
    Test t(10);
    Test s(20);
}
~~~
In this program, i is a constant data member, in every object its independent copy will be present, hence it is initialized with each object using the constructor. And once initialized, its value cannot be changed. The above way of initializing a class member is known as Initializer List in C++.



## 5 Defining Class's Member function as const
A const member functions never modifies data members in an object.
~~~
class StarWars
{
    public:
    int i;
    StarWars(int x)    // constructor
    { 
        i = x; 
    }

    int falcon() const  // constant function
    { 
        /* 
            can do anything but will not
            modify any data members
        */
        cout << "Falcon has left the Base";
    }

    int gamma()
    { 
        i++; 
    }
};

int main()
{
    StarWars objOne(10);        // non const object
    const StarWars objTwo(20);      // const object

    objOne.falcon();     // No error
    objTwo.falcon();     // No error

    cout << objOne.i << objTwo.i;

    objOne.gamma();     // No error
    objTwo.gamma();     // Compile time error
}
~~~
output
~~~
Falcon has left the Base
Falcon has left the Base
10 20
~~~

Here, we can see, that const member function never changes data members of class, and it can be used with both const and non-const objecta. But a const object cannot be used with a member function which tries to change its data members.

### mutable Keyword
mutable keyword is used with member variables of class, which we want to change even if the object is of const type. Hence, mutable data members of a const objects can be modified.
~~~
class Zee
{
    int i;
    mutable int j;
    public:
    Zee()
    {
        i = 0; 
        j = 0;
    }
    
    void fool() const
    { 
        i++;    // will give error
        j++;    // works, because j is mutable
    }
};

int main()
{
    const Zee obj;
    obj.fool();
}
~~~

## 6 Defining Class Object as const
When an object is declared or created using the const keyword, its data members can never be changed, during the object's lifetime.

Syntax:
~~~
const class_name object;
~~~
For example, if in the class Test defined above, we want to define a constant object, we can do it like:
~~~
const Test r(30);
~~~
