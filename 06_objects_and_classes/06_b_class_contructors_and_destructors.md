# 1 class constructor
when you create a object or instance of a class, you actuallu call the class's constructor method. and you can define your own constructor method, which ensentially a class member function.


## 1.1 declaraing and defining constructors

the name of constructor funtion is the same as the class name.
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

    how to construct with *new*:
    Stock *pstock = new Stock("Electrshock Games", 18, 19.0)
 
(3) list-initialization syntax with class in c++ 11.
    Stock jock{"derivation plus", 100, 45.0};

