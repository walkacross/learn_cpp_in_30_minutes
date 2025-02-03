# 1 the *const* Qualifier

let's return to the topic of symbolic names for constants. if the program uses the constant in several places and you need to change the value, you can just change the single sumbol definition. what if you want the prgram has no ability to change a constant value after it's first declaration and definition? the answer id use *const* qualifier.

~~~
const int Months = 12;         // Months is a symbolic constant for 12, read-only
~~~

if you define a constant such as Months by *const* qualifier, its value is set. the compilier doesn't let you subsequently change the value Months. if you try to, for example, g++ gives an error message that the program used an assignment of a read-only variable.

the keyword *const* is termed a *qualifier* because it qualifiers the meaning of a declaration.

# 2 *const* and pointers

you can use the *const* keyword two different ways with pointer.

* (1) the first way is to make a pointer point to a constant object, and that prevents you from pointer to change the pointed-to value.

* (2) the second way is to make the pointer itself constant constant, that prevents you form changing where the pointer points.


for (1):
~~~
int age = 39;
const int* pt = &age;
~~~

after that definition:

~~~
*pt += 1;         //invalid because pt pinters to a const int
cin >> *pt;       //invalid
~~~

~~~
*pt = 20;     // invalid
age = 20;     // here important.  Valid, because age is not declared to be cons
~~~

* this const declaration only prevent you from changine the value to which pt points, which is 39, but it doesn't prevent from changing the value of age and changing the value of pt itself
~~~
int sage = 80;
const int * pt = &age;
~~~


~~~
const float g_earth = 9.80;
const float * pe = &g_earth;  // valid
~~~
here, you can use neither g_earch nor pe to change the value.

~~~
const float g_moon = 1.63;
float* pm = &g_moon;     //invalid
~~~
c++ prohibits you from assigning the address of a const to a non-const pointer.


~~~
int sloth = 3;
const int* ps = &sloth;
int* const finger = &sloth;
~~~
note that the last declaration has repositioned the keyword const. this form of declaration constrains finger to the point only to sloth. however it allows you to use finger to alter the value of sloth.

the middle declaration does not allow you use ps to alter the value of sloth, but it permit you to have ps point to another location.

in short, finger and *ps are both const, and *finger and ps are not const.

if you like:
~~~
double trouble = 2.345;
const double * const stick = &trouble;
~~~
here, stick can point only to trouble adn stick cannot be used to change the value of trouble. in short both stick and *stick are const.

# 3 *const* and funtion argument
typically, you use the *const* qutifier form to protect data when you pass argument to funtion.

~~~
void show_argument(const int a)
{
    cout << "should not modify the argument " << a;
}

void display_argument(const int* p)
{
    cout << "should not modify the argument " << p;
}

~~~



# 4 conclusion
from the perspective of data object, the data object has a hidden attribute is whether allowed to be modified.

~~~
data_object.name
data_object.type     // class name
data_object.value
data_object.memory_address
data_object.duration    // use *static* to set this attribute, default is autimation
data_object.scope
data_object.linkage    // use *external* to set this attribute, default is true

data_object.whether_modify  // use *const* keyword to set this attributes,default is ture
~~~

**using *const* when you can**

there are to strong reason to declare pointer argument as pointers to constant data:

* it protect you against programming error that inadvertently alter data.
* using *const* allows a funtion to process both const and non-const actual arguments, whereas a funtion that omits const in the prototype can accept only non-const data. 

you should declare formal pointer arguments as pointer to const whenever it's appropiate to do so.



 
