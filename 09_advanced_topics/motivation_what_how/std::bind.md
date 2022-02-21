
> https://stackoverflow.com/questions/6610046/stdfunction-and-stdbind-what-are-they-and-when-should-they-be-used

**std::bind is for partial function application.**

That is, suppose you have a function object f which takes 3 arguments:
~~~
f(a,b,c);
~~~

You want a new function object which only takes two arguments, defined as:
~~~
g(a,b) := f(a, 4, b);
~~~
g is a "partial application" of the function f: the middle argument has already been specified, and there are two left to go.

You can use std::bind to get g:
~~~
auto g = bind(f, _1, 4, _2);
~~~
This is more concise than actually writing a functor class to do it.

There are further examples in the article you link to. You generally use it when you need to pass a functor to some algorithm. You have a function or functor that almost does the job you want, but is more configurable (i.e. has more parameters) than the algorithm uses. So you bind arguments to some of the parameters, and leave the rest for the algorithm to fill in:
~~~
// raise every value in vec to the power of 7
std::transform(vec.begin(), vec.end(), some_output, std::bind(std::pow, _1, 7));
~~~
Here, pow takes two parameters and can raise to any power, but all we care about is raising to the power of 7.
