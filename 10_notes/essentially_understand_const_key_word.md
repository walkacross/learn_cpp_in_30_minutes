The rule is:

> const applies to the thing left of it. If there is nothing on the left then it applies to the thing right of it.




You generally read types in C++ from right-to-left, for example Object const * is a pointer to a const Object. If you put the const on the left, it would read as a pointer to an Object that is const,
, which doesn't really flow very well


~~~
Object * const obj;        // read right-to-left:  const pointer to Object
Object const * obj;        // read right-to-left:  pointer to const Object
Object const * const obj;  // read right-to-left:  const pointer to const Object
~~~
