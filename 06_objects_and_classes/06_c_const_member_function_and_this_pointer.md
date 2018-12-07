# 1 class scope
class scope applies to names defined in a class, such as the names of class member variable and member functions. attributes that have class scope are only known withn the class but not ouside the class.
~~~
Stock sleeper("abcd", 100, 23.2);    //create object
sleeper.show();                      // use object to invoke a member funtion
show();                            //invalid -- cannot call methods directly
~~~

**class scope constant**

how to create a synbolic constant within class scope?

> declaring a class describes what an object looks like but doesn't create an object. Hence, until you create an object, there is no place to store a value.

~~~
class Baker
{
private:
    const int Months = 12;         // declare a constant? failed
    static const int Month = 12;   // vlaid
}
~~~
this create a single constant called Months that is stored with other static variables rather than in an object. 



# 2 const member function
how to make a function to promise not to modify the invoking object. the c++ solution is to place the *const* keyword after the funtion parentheses. something form like
~~~
void show() const;      //promise not to change invoking object
~~~

similarly, the beginning og the function definition should look like this:
~~~
void Stock::show() const    //promise not to change invoking object
~~~


# 3 how you provide the member funtion with two objects to compay?

~~~
const Stock& Stock::topval(const Stock & s) const
{
    if (s.total_val < total_val)
        return s;                //return argument object
    else
        return ????;             // return the invoking object itself
}
~~~

the c++ solution to this problem is to use a special pointer called *this*. the *this* pointer points to the object used to invoke a member funtion.

so the answer above is return *this;
