# understand Smart Pointer in c++

Pointers in C and C++ languages are wild beasts. They are extremely powerful, yet so dangerous: a little oversight may wreak havoc on your whole app.
The problem: their management is completely left up to you. Every dynamically allocated object (i.e. new T) must be followed by a manual deallocation (i.e. delete T). 
HAVE NO CHANCE TO DO THAT(meet exception before delete T) or Forget to do that and you will end up with a nice memory leak.

Another subtle problem lies in ownership. When it comes to dynamically-allocated objects, we often talk about who "owns" the object. "Owning" something
means it is yours to keep or destroy as you see fit. In C++, by ownership, we mean not just which code gets to refer
to or use the object, but mostly what code is responsible for deleting it. when a third-party function returns a pointer: is it dynamically-allocated data? If so, who is responsible for the cleanup? There is no way to infer such information by simply looking at the return type.

Smart pointers were born to fix the annoyances mentioned above. They basically provide automatic memory management: when a smart pointer is no longer in use, that is when it goes out of scope or  if you assigned them with a nullptr, the memory it points to is deallocated automatically. Traditional pointers are now also known as raw pointers.

> I like to think of smart pointers as boxes that hold the dynamic data. In fact they are just classes that wrap the raw pointer in their bowels and overload the -> and * operators. Thanks to this trick a smart pointer offers the same syntax of a raw one. When a smart pointer goes out of scope, its destructor gets triggered and the memory cleanup is performed. This technique is called Resource Acquisition Is Initialization (RAII): a class wrapped around a dynamic resource (file, socket, database connection, allocated memory, ...) that gets properly deleted/closed in its destructor. This way you are sure to avoid resource leaks.


## Types of smart pointers in modern C++
C++11 has introduced three types of smart pointers, all of them defined in the <memory> header from the Standard Library:
  
* *std::unique_ptr* — a smart pointer that owns a dynamically allocated resource;
* *std::shared_ptr* — a smart pointer that owns a shared dynamically allocated resource. Several std::shared_ptrs may own the same resource and an internal counter keeps track of them;
* *std::weak_ptr* — like a std::shared_ptr, but it doesn't increment the counter.
  
  
## 1 Understanding std::unique_ptr: the lone one
A *std::unique_ptr* owns of the object it points to and no other smart pointers can point to it. When the *std::unique_ptr* goes out of scope, the object is deleted. This is useful when you are working with a temporary, 
  dynamically-allocated resource that can get destroyed once out of scope.

### 1-a How to construct a std::unique_ptr
A std::unique_ptr is created like this:
~~~
std::unique_ptr<Type> p(new Type);
~~~
  
 For example:
~~~
std::unique_ptr<int>    p1(new int);
std::unique_ptr<int[]>  p2(new int[50]);
std::unique_ptr<Object> p3(new Object("Lamp")); 
~~~
  
It is also possible to construct std::unique_ptrs with the help of the special function std::make_unique, like this:
~~~
std::unique_ptr<Type> p = std::make_unique<Type>(...size or parameters...);
~~~

for example
~~~
std::unique_ptr<int>    p1 = std::make_unique<int>();
std::unique_ptr<int[]>  p2 = std::make_unique<int[]>(50);
std::unique_ptr<Object> p3 = std::make_unique<Object>("Lamp");
~~~

> If you can, always prefer to allocate objects using std::make_unique. I'll show you why in the last section of this article.

### 1-b how std::unique_ptr work
The main feature of this smart pointer is to vanish when no longer in use. Consider this:
~~~
void compute()
{
    std::unique_ptr<int[]> data = std::make_unique<int[]>(1024);
    /* do some meaningful computation on your data...*/
} // `data` goes out of scope here: it is automatically destroyed

int main()
{
    compute();
}
~~~
The smart pointer goes out of scope when the compute() function reaches the end of its body. It's destructor is invoked and the memory cleaned up automatically. No need to take care of anything else.

### 1-c One resource, one std::unique_ptr
A unique_ptr is a type of smart pointer that enforces that objects are owned by exactly one unique_ptr. This is in complete contrast with shared_ptr, where an object can be managed by several shared_ptr. This unique ownership is enforced by disallowing copy construction and copy assignment. So you can't copy or assign a unique_ptr to another unique_ptr.

So how do you declare a unique_ptr? Here is an example:
~~~
void foo(){
  //create the unique_ptr and assign an object to manage
  unique_ptr<MyObject> p1(new MyObject());

  //Copy construction is not allowed
  unique_ptr<MyObject> p2(p1);

  //Copy assignment is also not allowed
  unique_ptr<MyObject> p3;
  p3=p1;
}
~~~
Technically this happens because a std::unique_ptr doesn't have a copy constructor: it might be obvious to you if you are familiar with move semantics. Although copy constructor and copy assignments are not defined in unique_ptr, move constructor and move assignments are defined. Thus, a unique_ptr can transfer ownership of a managed object. After a move construction the newly created unique_ptr owns the object and the original unique_ptr owns nothing.
 
This comes in handy when a method returns a unique_ptr. Since the returned value of a method is a rvalue, the presence of move construction and move assignment means that we can return a unique_ptr from a method and assign it to another unique_ptr. For example:
~~~
unique_ptr<MyObject> createPointer(){
  //create a local unique pointer
  unique_ptr<MyObject> p1(new MyObject());

  return p1; // p1 will surrender ownership
}

void main(){
  unique_ptr<MyObject> a1; //unique_ptr points to nothing
  a1=createPointer(); //now a1 owns the object
}
~~~

  
# reference
https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
 
