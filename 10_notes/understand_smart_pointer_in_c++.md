# understand Smart Pointer in c++

Pointers in C and C++ languages are wild beasts. They are extremely powerful, yet so dangerous: a little oversight may wreak havoc on your whole app.
The problem: their management is completely left up to you. Every dynamically allocated object (i.e. new T) must be followed by a manual deallocation (i.e. delete T). 
HAVE NO CHANCE TO DO THAT(meet exception before delete T) or Forget to do that and you will end up with a nice memory leak.

Another subtle problem lies in ownership. When it comes to dynamically-allocated objects, we often talk about who "owns" the object. "Owning" something
means it is yours to keep or destroy as you see fit. In C++, by ownership, we mean not just which code gets to refer
to or use the object, but mostly what code is responsible for deleting it. when a third-party function returns a pointer: is it dynamically-allocated data? If so, who is responsible for the cleanup? There is no way to infer such information by simply looking at the return type.

~~~
// case1: throw error before delete
A* p = new A;
...// have error here, and have no chance to call delete
delete p

//case2: allocate and release memory at different function

A* create_A(){
  A* p = new A;
  return p;
}

void f(){
  A* p  = create_A();
  ...// forget to delete, who should be resposible for delete p
  delete p;
}

//case3: Object Slicing
~~~


Smart pointers were born to fix the annoyances mentioned above. They basically provide automatic memory management: when a smart pointer is no longer in use, that is when it goes out of scope or if you assigned them with a nullptr, the memory it points to is deallocated automatically. Traditional pointers are now also known as raw pointers.

> I like to think of smart pointers as boxes that hold the dynamic data. In fact they are just classes that wrap the raw pointer in their bowels and overload the -> and * operators. Thanks to this trick a smart pointer offers the same syntax of a raw one. When a smart pointer goes out of scope, its destructor gets triggered and the memory cleanup is performed. This technique is called Resource Acquisition Is Initialization (RAII): a class wrapped around a dynamic resource (file, socket, database connection, allocated memory, ...) that gets properly deleted/closed in its destructor. This way you are sure to avoid resource leaks.


## Types of smart pointers in modern C++
a smart pointer is a class that manages a dynamically allocated object. C++11 has introduced three types of smart pointers, all of them defined in the <memory> header from the Standard Library:
  
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
#include <iostream>
#include <memory> // for std::unique_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	// allocate a Resource object and have it owned by std::unique_ptr
	std::unique_ptr<Resource> res{ new Resource() };
 
	return 0;
} // res goes out of scope here, and the allocated Resource is destroyed
~~~
Because the std::unique_ptr is allocated on the stack here, it’s guaranteed to eventually go out of scope, and when it does, it will delete the Resource it is managing.
  
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

~~~
#include <iostream>
#include <memory> // for std::unique_ptr
#include <utility> // for std::move
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
	std::unique_ptr<Resource> res2{}; // Start as nullptr
 
	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
 
	// res2 = res1; // Won't compile: copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
 
	std::cout << "Ownership transferred\n";
 
	std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n");
	std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n");
 
	return 0;
} // Resource destroyed here when res2 goes out of scope
~~~
This prints:
~~~
Resource acquired
res1 is not null
res2 is null
Ownership transferred
res1 is null
res2 is not null
Resource destroyed
~~~

Because std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment are disabled. If you want to transfer the contents managed by std::unique_ptr, you must use move semantics. In the program above, we accomplish this via std::move (which converts res1 into an r-value, which triggers a move assignment instead of a copy assignment).  

Accessing the managed object

std::unique_ptr has an overloaded operator* and operator-> that can be used to return the resource being managed. Operator* returns a reference to the managed resource, and operator-> returns a pointer.

Remember that std::unique_ptr may not always be managing an object -- either because it was created empty (using the default constructor or passing in a nullptr as the parameter), or because the resource it was managing got moved to another std::unique_ptr. So before we use either of these operators, we should check whether the std::unique_ptr actually has a resource. Fortunately, this is easy: std::unique_ptr has a cast to bool that returns true if the std::unique_ptr is managing a resource.

Here’s an example of this:
~~~
#include <iostream>
#include <memory> // for std::unique_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
	friend std::ostream& operator<<(std::ostream& out, const Resource &res)
	{
		out << "I am a resource\n";
		return out;
	}
};
 
int main()
{
	std::unique_ptr<Resource> res{ new Resource{} };
 
	if (res) // use implicit cast to bool to ensure res contains a Resource
		std::cout << *res << '\n'; // print the Resource that res is owning
 
	return 0;
}
~~~
This prints:
~~~
Resource acquired
I am a resource
Resource destroyed
~~~
In the above program, we use the overloaded operator* to get the Resource object owned by std::unique_ptr res, which we then send to std::cout for printing.  

### 1-d: Passing std::unique_ptr to a function
If you want the function to take ownership of the contents of the pointer, pass the std::unique_ptr by value. Note that because copy semantics have been disabled, you’ll need to use std::move to actually pass the variable in.
~~~
#include <memory> // for std::unique_ptr
#include <utility> // for std::move
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
	friend std::ostream& operator<<(std::ostream& out, const Resource &res)
	{
		out << "I am a resource\n";
		return out;
	}
};
 
void takeOwnership(std::unique_ptr<Resource> res)
{
     if (res)
          std::cout << *res << '\n';
} // the Resource is destroyed here
 
int main()
{
    auto ptr{ std::make_unique<Resource>() };
 
//    takeOwnership(ptr); // This doesn't work, need to use move semantics
    takeOwnership(std::move(ptr)); // ok: use move semantics
 
    std::cout << "Ending program\n";
 
    return 0;
}
~~~

The above program prints:
~~~
Resource acquired
I am a resource
Resource destroyed
Ending program
~~~
Note that in this case, ownership of the Resource was transferred to takeOwnership(), so the Resource was destroyed at the end of takeOwnership() rather than the end of main().

However, most of the time, you won’t want the function to take ownership of the resource. Although you can pass a std::unique_ptr by reference (which will allow the function to use the object without assuming ownership), you should only do so when the called function might alter or change the object being managed.

Instead, it’s better to just pass the resource itself (by pointer or reference, depending on whether null is a valid argument). This allows the function to remain agnostic of how the caller is managing its resources. To get a raw resource pointer from a std::unique_ptr, you can use the get() member function
~~~
#include <memory> // for std::unique_ptr
#include <iostream>
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
 
	friend std::ostream& operator<<(std::ostream& out, const Resource &res)
	{
		out << "I am a resource\n";
		return out;
	}
};
 
// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void useResource(Resource *res)
{
	if (res)
		std::cout << *res << '\n';
}
 
int main()
{
	auto ptr{ std::make_unique<Resource>() };
 
	useResource(ptr.get()); // note: get() used here to get a pointer to the Resource
 
	std::cout << "Ending program\n";
 
	return 0;
} // The Resource is destroyed here  
~~~
The above program prints:
~~~
Resource acquired
I am a resource
Ending program
Resource destroyed  
~~~

  
### 1-e: Returning std::unique_ptr from a function
std::unique_ptr can be safely returned from a function by value. This comes in handy when a method returns a unique_ptr. Since the returned value of a method is a rvalue, the presence of move construction and move assignment means that we can return a unique_ptr from a method and assign it to another unique_ptr. For example:
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
~~~
std::unique_ptr<Resource> createResource()
{
     return std::make_unique<Resource>();
}
 
int main()
{
    auto ptr{ createResource() };
 
    // do whatever
 
    return 0;
}
~~~
In the above code, createResource() returns a std::unique_ptr by value. If this value is not assigned to anything, the temporary return value will go out of scope and the Resource will be cleaned up. If it is assigned (as shown in main()), in C++14 or earlier, move semantics will be employed to transfer the Resource from the return value to the object assigned to (in the above example, ptr), and in C++17 or newer, the return will be elided. This makes returning a resource by std::unique_ptr much safer than returning raw pointers!

In general, you should not return std::unique_ptr by pointer (ever) or reference (unless you have a specific compelling reason to).

### 1-f: Misusing std::unique_ptr
There are two easy ways to misuse std::unique_ptrs, both of which are easily avoided. First, don’t let multiple classes manage the same resource. For example:
~~~
Resource *res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
std::unique_ptr<Resource> res2{ res };
~~~
While this is legal syntactically, the end result will be that both res1 and res2 will try to delete the Resource, which will lead to undefined behavior.

Second, don’t manually delete the resource out from underneath the std::unique_ptr.
~~~
Resource *res{ new Resource() };
std::unique_ptr<Resource> res1{ res };
delete res;
~~~
If you do, the std::unique_ptr will try to delete an already deleted resource, again leading to undefined behavior.

Note that std::make_unique() prevents both of the above cases from happening inadvertently.

## 2 understand std::shared_ptr
Unlike std::unique_ptr, which is designed to singly own and manage a resource, std::shared_ptr is meant to solve the case where you need multiple smart pointers co-owning a resource. that is designed for scenarios in which more than one owner might have to manage the lifetime of the object in memory.

This means that it is fine to have multiple std::shared_ptr pointing to the same resource. Internally, std::shared_ptr keeps track of how many std::shared_ptr are sharing the resource. As long as at least one std::shared_ptr is pointing to the resource, the resource will not be deallocated, even if individual std::shared_ptr are destroyed. As soon as the last std::shared_ptr managing the resource goes out of scope (or is reassigned to point at something else), the resource will be deallocated.

in summary, The shared_ptr class template is a referenced-counted smart pointer; a count is kept of how many smart pointers are pointing to the managed object; when the last smart pointer is destroyed, the count goes to zero, and the managed object is then automatically deleted. It is called a "shared" smart pointer because the smart pointers all
share ownership of the managed object - any one of the smart pointers can keep the object in existence; it gets deleted only when no smart pointers point to it any more.

### 2-a How to construct a std::shared_ptr
A std::shared_ptr is constructed like this:
~~~
std::shared_ptr<Type> p(new Type);
~~~

For example:
~~~
std::shared_ptr<int>    p1(new int);
std::shared_ptr<Object> p2(new Object("Lamp"));
~~~

  
There is an alternate way to build a std::shared_ptr, powered by the special function std::make_shared:
~~~
std::shared_ptr<Type> p = std::make_shared<Type>(...parameters...);
~~~
For example:
~~~
std::shared_ptr<int>    p1 = std::make_shared<int>();
std::shared_ptr<Object> p2 = std::make_shared<Object>("Lamp");
~~~
> This should be the preferred way to construct this kind of smart pointer. 

## 2-b how std::shared_ptr work
~~~
void foo(){
  //create the shared_ptr and assign an object to manage
  shared_ptr<MyObject> mySmartPointer(new MyObject());

  //create a second shared_ptr and share the object
  shared_ptr<MyObject> anotherSmartObject=mySmartPointer; 

  //count up to now is 2
  //set mySmartPointer to nullptr
  mySmartPointer=nullptr; 

  //count now is 1, thus the object will not be released

  //set anotherSmartObject to nullptr
  anotherSmartObject=nullptr;
  //count is now zero, thus the object will be released

  //...Do other stuffs here
}
~~~
  
  
~~~
#include <iostream>
#include <memory> // for std::shared_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	// allocate a Resource object and have it owned by std::shared_ptr
	Resource *res = new Resource;
	std::shared_ptr<Resource> ptr1(res);
	{
		std::shared_ptr<Resource> ptr2(ptr1); // use copy initialization to make another std::shared_ptr pointing to the same thing
 
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed
~~~

This prints:
~~~  
Resource acquired
Killing one shared pointer
Killing another shared pointer
Resource destroyed
~~~  
In the above code, we create a dynamic Resource object, and set a std::shared_ptr named ptr1 to manage it. Inside the nested block, we use copy initialization (which is allowed with std::shared_ptr, since the resource can be shared) to create a second std::shared_ptr (ptr2) that points to the same Resource. When ptr2 goes out of scope, the Resource is not deallocated, because ptr1 is still pointing at the Resource. When ptr1 goes out of scope, ptr1 notices there are no more std::shared_ptr managing the Resource, so it deallocates the Resource.

Note that we created a second shared pointer from the first shared pointer (using copy initialization). This is important. Consider the following similar program:
~~~
#include <iostream>
#include <memory> // for std::shared_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	Resource *res = new Resource;
	std::shared_ptr<Resource> ptr1(res);
	{
		std::shared_ptr<Resource> ptr2(res); // create ptr2 directly from res (instead of ptr1)
 
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, and the allocated Resource is destroyed
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed again
~~~
  
this prints
~~~
Resource acquired
Killing one shared pointer
Resource destroyed
Killing another shared pointer
Resource destroyed
~~~
and then crashes (at least on the author’s machine).

The difference here is that we created two std::shared_ptr independently from each other. As a consequence, even though they’re both pointing to the same Resource, they aren’t aware of each other. When ptr2 goes out of scope, it thinks it’s the only owner of the Resource, and deallocates it. When ptr1 later goes out of the scope, it thinks the same thing, and tries to delete the Resource again. Then bad things happen.

Fortunately, this is easily avoided by using copy assignment or copy initialization when you need multiple shared pointers pointing to the same Resource.
> Best practice: Always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing to the same resource.

std::make_shared

Much like std::make_unique() can be used to create a std::unique_ptr in C++14, std::make_shared() can (and should) be used to make a std::shared_ptr. std::make_shared() is available in C++11.

Here’s our original example, using std::make_shared():
~~~
#include <iostream>
#include <memory> // for std::shared_ptr
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	// allocate a Resource object and have it owned by std::shared_ptr
	auto ptr1 = std::make_shared<Resource>();
	{
		auto ptr2 = ptr1; // create ptr2 using copy initialization of ptr1
 
		std::cout << "Killing one shared pointer\n";
	} // ptr2 goes out of scope here, but nothing happens
 
	std::cout << "Killing another shared pointer\n";
 
	return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed
~~~
The reasons for using std::make_shared() are the same as std::make_unique() -- std::make_shared() is simpler and safer (there’s no way to directly create two std::shared_ptr pointing to the same resource using this method). However, std::make_shared() is also more performant than not using it. The reasons for this lie in the way that std::shared_ptr keeps track of how many pointers are pointing at a given resource.

**Digging into std::shared_ptr**

Unlike std::unique_ptr, which uses a single pointer internally, std::shared_ptr uses two pointers internally. One pointer points at the resource being managed. The other points at a “control block”, which is a dynamically allocated object that tracks of a bunch of stuff, including how many std::shared_ptr are pointing at the resource. When a std::shared_ptr is created via a std::shared_ptr constructor, the memory for the managed object (which is usually passed in) and control block (which the constructor creates) are allocated separately. However, when using std::make_shared(), this can be optimized into a single memory allocation, which leads to better performance.

This also explains why independently creating two std::shared_ptr pointed to the same resource gets us into trouble. Each std::shared_ptr will have one pointer pointing at the resource. However, each std::shared_ptr will independently allocate its own control block, which will indicate that it is the only pointer owning that resource. Thus, when that std::shared_ptr goes out of scope, it will deallocate the resource, not realizing there are other std::shared_ptr also trying to manage that resource.

However, when a std::shared_ptr is cloned using copy assignment, the data in the control block can be appropriately updated to indicate that there are now additional std::shared_ptr co-managing the resource.
  
# reference
https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
 
