# 1 Funtion Templates

in some case, a funtion focuses on executing some logics rather than depend on the type of argument.

> A function template is a generic funtion description; that is, it defines a function in terms of a generic type for which a specific type, such as int or double, can be substituted.

~~~
#include <iostream>

// function template prototype
template<typename T>
void swap(T &a, T &b);

int main()
{
    using namespace std;
    int i = 10;
    int j = 20;
    cout << "i, j = " << i << ", " << j << ".\n";
    cout << "using compiler-generated int swapper:\n";
    swap(i,j);
    cout << "Now i, j = " << i << ", " << j << ".\n";

    double x = 24.5;
    double y = 81.7;
    cout << "x, y = " << x << ", " << y << ".\n";
    cout << "using compiler-generated double swapper:\n";
    swap(x,y);
    count << "now x, y = " << x << ", " << y << ".\n";
    
    return 0;
}


// funtion template definition
template <typename T>   // or class T
void swap( T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
~~~

recall, a data object is a object who has some attribute to identify it.
~~~
data_object.name
data_object.value
data_object.type  // int, double, char
data_object.size
data_object.store_address
~~~

there are many perspective of category data_object,according to the type of value, the data object can be category into general variable, reference and pointer.

