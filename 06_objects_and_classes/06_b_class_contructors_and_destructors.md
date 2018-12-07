# 1 class constructor
when you create a object or instance of a class, you actually call the class's constructor method. and you can define your own constructor method, which ensentially a class member function.


## 1.1 declaraing and defining constructors

the name of constructor funtion is the same as the class name. and can have no return type.
~~~
// class contructor declaration
class Stock
{
private:
    ...

public:
    Stock(const string & co, long n, double pr);
}
~~~

~~~
// contructor  definition
Stock::Stock(const string & co, long n, double pr)
{
    company_name = co;
    if (n < 0)
    {
        std::cout << "can not be negative";
        shares = 0;
    }
    else:
        shares = n;
    share_val = pr;
    set_tot();
}
~~~


## 1.2 using constructors
c++ provide three ways to create (initialize) an object by using a constructor.

(1) the first is to call the constructor explicitly:
   
 Stock food = Stock("world cabbage", 250, 1.25);

(2) the second way os to call the constructor implicitly:
   
 Stock garment("Furry Mason", 50, 2.5)


(3) list-initialization syntax with class in c++ 11.

    Stock jock{"derivation plus", 100, 45.0};

>how to construct with *new*:
Stock *pstock = new Stock("Electrshock Games", 18, 19.0)

## 1.3 default constructor

a *default constructor* is a constructor that is used to create an object when you don't provide explicit initialization values. that is, it's a constructor used for declarations like this:
~~~
Stock fluffy_the_cat;          // uses the default constructor
~~~ 

a default constructor would like this:
~~~
Stock::Stock(){}
~~~

A curious fact about default constructor is that: the compiler provides one only if you don't define any constructors. after you define any constructor for a class, the resonsibility for providing a default constructor for that class passes from the compilier to you.

you might define a defautl constructor like this
~~~
Stock::stock()
{
    conpany_name = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}
~~~


# 2 Class Destructor
according to the duration of a object, when it expires, the compiler will call the deconstrctor member function to delete it. generally, you can simply let the compiler generate an default, implicit, do-nothing destructor. on the other hand, you can define your own destructor funtion to behave something.

(1) a destructor has a special name: it is formed from the class name preceded by a tilde (~)

(2) can have no return value and has no declared type

(3) a destructor must have no arguments.

~~~
Stock::~Stock()
{
    cout << "bye, " << company_name << "\n";
}
~~~


when should a destructor be called? the compiler handles this decision; normally your code should not explicitly call a destructor.

according the duration of a object, the destructor is called automatically when a class object expires.

