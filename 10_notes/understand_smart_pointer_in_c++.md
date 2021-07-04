# understand Smart Pointer in c++

# 1 motivation to smart pointers and move semantics,
Pointers in C and C++ languages are wild beasts. They are extremely powerful, yet so dangerous: a little oversight may wreak havoc on your whole app.
The problem: their management is completely left up to you. Every dynamically allocated object (i.e. new T) must be followed by a manual deallocation (i.e. delete T). 
HAVE NO CHANCE TO DO THAT(meet exception before delete T) or Forget to do that and you will end up with a nice memory leak.

~~~
// case1: throw error before delete
void someFunction()
{
    Resource *ptr = new Resource(); // Resource is a struct or class
 
    // do stuff with ptr here
 
    delete ptr;
}
~~~
Although the above code seems fairly straightforward, it’s fairly easy to forget to deallocate ptr. Even if you do remember to delete ptr at the end of the function, there are a myriad of ways that ptr may not be deleted if the function exits early. This can happen via an early return or via a thrown exception:
~~~
#include <iostream>
 
void someFunction()
{
    Resource *ptr = new Resource();
 
    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
 
    if (x == 0)
        return 0;//throw 0; // the function returns early, and ptr won’t be deleted!
 
    // do stuff with ptr here
 
    delete ptr;
}
~~~
In the above two programs, the early return or throw statement execute, causing the function to terminate without variable ptr being deleted. Consequently, the memory allocated for variable ptr is now leaked (and will be leaked again every time this function is called and returns early).

At heart, these kinds of issues occur because pointer variables have no inherent mechanism to clean up after themselves.

One of the best things about classes is that they contain destructors that automatically get executed when an object of the class goes out of scope. So if you allocate (or acquire) memory in your constructor, you can deallocate it in your destructor, and be guaranteed that the memory will be deallocated when the class object is destroyed (regardless of whether it goes out of scope, gets explicitly deleted, etc…). This is at the heart of the RAII programming paradigm that we talked about in lesson 12.9 -- Destructors.

So can we use a class to help us manage and clean up our pointers? We can!

Consider a class whose sole job was to hold and “own” a pointer passed to it, and then deallocate that pointer when the class object went out of scope. As long as objects of that class were only created as local variables, we could guarantee that the class would properly go out of scope (regardless of when or how our functions terminate) and the owned pointer would get destroyed.

Here’s a first draft of the idea:
~~~
#include <iostream>
 
template<class T>
class Auto_ptr1
{
	T* m_ptr;
public:
	// Pass in a pointer to "own" via the constructor
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}
	
	// The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}
 
	// Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};
 
// A sample class to prove the above works
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	Auto_ptr1<Resource> res(new Resource()); // Note the allocation of memory here
 
        // ... but no explicit delete needed
 
	// Also note that the Resource in angled braces doesn't need a * symbol, since that's supplied by the template
 
	return 0;
} // res goes out of scope here, and destroys the allocated Resource for us
~~~

~~~
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
This program prints:
~~~
Resource acquired
Resource destroyed
~~~
Consider how this program and class work. First, we dynamically create a Resource, and pass it as a parameter to our templated Auto_ptr1 class. From that point forward, our Auto_ptr1 variable res owns that Resource object (Auto_ptr1 has a composition relationship with m_ptr). Because res is declared as a local variable and has block scope, it will go out of scope when the block ends, and be destroyed (no worries about forgetting to deallocate it). And because it is a class, when it is destroyed, the Auto_ptr1 destructor will be called. That destructor will ensure that the Resource pointer it is holding gets deleted!

As long as Auto_ptr1 is defined as a local variable (with automatic duration, hence the “Auto” part of the class name), the Resource will be guaranteed to be destroyed at the end of the block it is declared in, regardless of how the function terminates (even if it terminates early).

Such a class is called a smart pointer. A Smart pointer is a composition class that is designed to manage dynamically allocated memory and ensure that memory gets deleted when the smart pointer object goes out of scope. (Relatedly, built-in pointers are sometimes called “dumb pointers” because they can’t clean up after themselves).

Now let’s go back to our someFunction() example above, and show how a smart pointer class can solve our challenge:
~~~
#include <iostream>
 
template<class T>
class Auto_ptr1
{
	T* m_ptr;
public:
	// Pass in a pointer to "own" via the constructor
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}
	
	// The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}
 
	// Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};
 
// A sample class to prove the above works
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};
 
void someFunction()
{
    Auto_ptr1<Resource> ptr(new Resource()); // ptr now owns the Resource
 
    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;
 
    if (x == 0)
        return; // the function returns early
 
    // do stuff with ptr here
    ptr->sayHi();
}
 
int main()
{
    someFunction();
 
    return 0;
}
~~~
If the user enters a non-zero integer, the above program will print:
~~~
Resource acquired
Hi!
Resource destroyed
~~~
If the user enters zero, the above program will terminate early, printing:
~~~
Resource acquired
Resource destroyed
~~~
Note that even in the case where the user enters zero and the function terminates early, the Resource is still properly deallocated.

Because the ptr variable is a local variable, ptr will be destroyed when the function terminates (regardless of how it terminates). And because the Auto_ptr1 destructor will clean up the Resource, we are assured that the Resource will be properly cleaned up.

### A critical flaw

The Auto_ptr1 class has a critical flaw lurking behind some auto-generated code. Before reading further, see if you can identify what it is. We’ll wait…

(Hint: consider what parts of a class get auto-generated if you don’t supply them)

(Jeopardy music)

Okay, time’s up.

Rather than tell you, we’ll show you. Consider the following program:
~~~
#include <iostream>
 
// Same as above
template<class T>
class Auto_ptr1
{
	T* m_ptr;
public:
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}
	
	~Auto_ptr1()
	{
		delete m_ptr;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	Auto_ptr1<Resource> res1(new Resource());
	Auto_ptr1<Resource> res2(res1); // Alternatively, don't initialize res2 and then assign res2 = res1;
 
	return 0;
}
~~~
This program prints:
~~~
Resource acquired
Resource destroyed
Resource destroyed
~~~
Very likely (but not necessarily) your program will crash at this point. See the problem now? Because we haven’t supplied a copy constructor or an assignment operator, C++ provides one for us. And the functions it provides do shallow copies. So when we initialize res2 with res1, both Auto_ptr1 variables are pointed at the same Resource. When res2 goes out of the scope, it deletes the resource, leaving res1 with a dangling pointer. When res1 goes to delete its (already deleted) Resource, crash!

You’d run into a similar problem with a function like this:
~~~
void passByValue(Auto_ptr1<Resource> res)
{
}
 
int main()
{
	Auto_ptr1<Resource> res1(new Resource());
	passByValue(res1)
 
	return 0;
}
~~~
In this program, res1 will be copied by value into passByValue’s parameter res, leading to duplication of the Resource pointer. Crash!

So clearly this isn’t good. How can we address this?

Well, one thing we could do would be to explicitly define and delete the copy constructor and assignment operator, thereby preventing any copies from being made in the first place. That would prevent the pass by value case (which is good, we probably shouldn’t be passing these by value anyway).

But then how would we return an Auto_ptr1 from a function back to the caller?
~~~
??? generateResource()
{
     Resource *r = new Resource();
     return Auto_ptr1(r);
}
~~~
We can’t return our Auto_ptr1 by reference, because the local Auto_ptr1 will be destroyed at the end of the function, and the caller will be left with a dangling reference. Return by address has the same problem. We could return pointer r by address, but then we might forget to delete r later, which is the whole point of using smart pointers in the first place. So that’s out. Returning the Auto_ptr1 by value is the only option that makes sense -- but then we end up with shallow copies, duplicated pointers, and crashes.

Another option would be to override the copy constructor and assignment operator to make deep copies. In this way, we’d at least guarantee to avoid duplicate pointers to the same object. But copying can be expensive (and may not be desirable or even possible), and we don’t want to make needless copies of objects just to return an Auto_ptr1 from a function. Plus assigning or initializing a dumb pointer doesn’t copy the object being pointed to, so why would we expect smart pointers to behave differently?

What do we do?

### Move semantics
What if, instead of having our copy constructor and assignment operator copy the pointer (“copy semantics”), we instead transfer/move ownership of the pointer from the source to the destination object? This is the core idea behind move semantics. Move semantics means the class will transfer ownership of the object rather than making a copy.

Let’s update our Auto_ptr1 class to show how this can be done:

~~~
#include <iostream>
 
template<class T>
class Auto_ptr2
{
	T* m_ptr;
public:
	Auto_ptr2(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}
	
	~Auto_ptr2()
	{
		delete m_ptr;
	}
 
	// A copy constructor that implements move semantics
	Auto_ptr2(Auto_ptr2& a) // note: not const
	{
		m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
		a.m_ptr = nullptr; // make sure the source no longer owns the pointer
	}
	
	// An assignment operator that implements move semantics
	Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
	{
		if (&a == this)
			return *this;
 
		delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
		m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
		a.m_ptr = nullptr; // make sure the source no longer owns the pointer
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr;  }
};
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
int main()
{
	Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr
 
	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
 
	res2 = res1; // res2 assumes ownership, res1 is set to null
 
	std::cout << "Ownership transferred\n";
 
	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");
 
	return 0;
}
~~~
This program prints:
~~~
Resource acquired
res1 is not null
res2 is null
Ownership transferred
res1 is null
res2 is not null
Resource destroyed
~~~
Note that our overloaded operator= gave ownership of m_ptr from res1 to res2! Consequently, we don’t end up with duplicate copies of the pointer, and everything gets tidily cleaned up.

### std::auto_ptr, and why it was a bad idea
Now would be an appropriate time to talk about std::auto_ptr. std::auto_ptr, introduced in C++98 and removed in C++17, was C++’s first attempt at a standardized smart pointer. std::auto_ptr opted to implement move semantics just like the Auto_ptr2 class does.

However, std::auto_ptr (and our Auto_ptr2 class) has a number of problems that makes using it dangerous.

First, because std::auto_ptr implements move semantics through the copy constructor and assignment operator, passing a std::auto_ptr by value to a function will cause your resource to get moved to the function parameter (and be destroyed at the end of the function when the function parameters go out of scope). Then when you go to access your auto_ptr argument from the caller (not realizing it was transferred and deleted), you’re suddenly dereferencing a null pointer. Crash!

Second, std::auto_ptr always deletes its contents using non-array delete. This means auto_ptr won’t work correctly with dynamically allocated arrays, because it uses the wrong kind of deallocation. Worse, it won’t prevent you from passing it a dynamic array, which it will then mismanage, leading to memory leaks.

Finally, auto_ptr doesn’t play nice with a lot of the other classes in the standard library, including most of the containers and algorithms. This occurs because those standard library classes assume that when they copy an item, it actually makes a copy, not a move.

Because of the above mentioned shortcomings, std::auto_ptr has been deprecated in C++11 and removed in C++17.

The core problem with the design of std::auto_ptr is that prior to C++11, the C++ language simply had no mechanism to differentiate “copy semantics” from “move semantics”. Overriding the copy semantics to implement move semantics leads to weird edge cases and inadvertent bugs. For example, you can write res1 = res2 and have no idea whether res2 will be changed or not!

Because of this, in C++11, the concept of “move” was formally defined, and “move semantics” were added to the language to properly differentiate copying from moving. Now that we’ve set the stage for why move semantics can be useful, we’ll explore the topic of move semantics throughout the rest of this chapter. We’ll also fix our Auto_ptr2 class using move semantics.

In C++11, std::auto_ptr has been replaced by a bunch of other types of “move-aware” smart pointers: std::unique_ptr, std::weak_ptr, and std::shared_ptr. We’ll also explore the two most popular of these: unique_ptr (which is a direct replacement for auto_ptr) and shared_ptr.

> Another subtle problem lies in ownership. When it comes to dynamically-allocated objects, we often talk about who "owns" the object. "Owning" something
means it is yours to keep or destroy as you see fit. In C++, by ownership, we mean not just which code gets to refer
to or use the object, but mostly what code is responsible for deleting it. when a third-party function returns a pointer: is it dynamically-allocated data? If so, who is responsible for the cleanup? There is no way to infer such information by simply looking at the return type.


> Smart pointers were born to fix the annoyances mentioned above. They basically provide automatic memory management: when a smart pointer is no longer in use, that is when it goes out of scope or if you assigned them with a nullptr, the memory it points to is deallocated automatically. Traditional pointers are now also known as raw pointers.

> I like to think of smart pointers as boxes that hold the dynamic data. In fact they are just classes that wrap the raw pointer in their bowels and overload the -> and * operators. Thanks to this trick a smart pointer offers the same syntax of a raw one. When a smart pointer goes out of scope, its destructor gets triggered and the memory cleanup is performed. This technique is called Resource Acquisition Is Initialization (RAII): a class wrapped around a dynamic resource (file, socket, database connection, allocated memory, ...) that gets properly deleted/closed in its destructor. This way you are sure to avoid resource leaks.

# 2 Move constructors and move assignment
In lesson M.1 -- Intro to smart pointers and move semantics, we took a look at std::auto_ptr, discussed the desire for move semantics, and took a look at some of the downsides that occur when functions designed for copy semantics (copy constructors and copy assignment operators) are redefined to implement move semantics.

In this lesson, we’ll take a deeper look at how C++11 resolves these problems via move constructors and move assignment.

## 2.1 Copy constructors and copy assignment
First, let’s take a moment to recap copy semantics.

Copy constructors are used to initialize a class by making a copy of an object of the same class. Copy assignment is used to copy one class object to another existing class object. By default, C++ will provide a copy constructor and copy assignment operator if one is not explicitly provided. These compiler-provided functions do shallow copies, which may cause problems for classes that allocate dynamic memory. So classes that deal with dynamic memory should override these functions to do deep copies.

Returning back to our Auto_ptr smart pointer class example from the first lesson in this chapter, let’s look at a version that implements a copy constructor and copy assignment operator that do deep copies, and a sample program that exercises them:
~~~
template<class T>
class Auto_ptr3
{
	T* m_ptr;
public:
	Auto_ptr3(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}
 
	~Auto_ptr3()
	{
		delete m_ptr;
	}
 
	// Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3(const Auto_ptr3& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}
 
	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3& operator=(const Auto_ptr3& a)
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Copy the resource
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
 
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
Auto_ptr3<Resource> generateResource()
{
	Auto_ptr3<Resource> res(new Resource);
	return res; // this return value will invoke the copy constructor
}
 
int main()
{
	Auto_ptr3<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the copy assignment
 
	return 0;
}
~~~
In this program, we’re using a function named generateResource() to create a smart pointer encapsulated resource, which is then passed back to function main(). Function main() then assigns that to an existing Auto_ptr3 object.

When this program is run, it prints:
~~~
Resource acquired
Resource acquired
Resource destroyed
Resource acquired
Resource destroyed
Resource destroyed
~~~
(Note: You may only get 4 outputs if your compiler elides the return value from function generateResource())

That’s a lot of resource creation and destruction going on for such a simple program! What’s going on here?
Let’s take a closer look. There are 6 key steps that happen in this program (one for each printed message):
~~~
1) Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource, which causes the first “Resource acquired”.
2) Res is returned back to main() by value. We return by value here because res is a local variable -- it can’t be returned by address or reference because res will be destroyed when generateResource() ends. So res is copy constructed into a temporary object. Since our copy constructor does a deep copy, a new Resource is allocated here, which causes the second “Resource acquired”.
3) Res goes out of scope, destroying the originally created Resource, which causes the first “Resource destroyed”.
4) The temporary object is assigned to mainres by copy assignment. Since our copy assignment also does a deep copy, a new Resource is allocated, causing yet another “Resource acquired”.
5) The assignment expression ends, and the temporary object goes out of expression scope and is destroyed, causing a “Resource destroyed”.
6) At the end of main(), mainres goes out of scope, and our final “Resource destroyed” is displayed.
~~~
So, in short, because we call the copy constructor once to copy construct res to a temporary, and copy assignment once to copy the temporary into mainres, we end up allocating and destroying 3 separate objects in total.

Inefficient, but at least it doesn’t crash!

However, with move semantics, we can do better.

## 2.2 Move constructors and move assignment

C++11 defines two new functions in service of move semantics: a move constructor, and a move assignment operator. Whereas the goal of the copy constructor and copy assignment is to make a copy of one object to another, the goal of the move constructor and move assignment is to move ownership of the resources from one object to another (which is typically much less expensive than making a copy).

Defining a move constructor and move assignment work analogously to their copy counterparts. However, whereas the copy flavors of these functions take a const l-value reference parameter, the move flavors of these functions use non-const r-value reference parameters.

Here’s the same Auto_ptr3 class as above, with a move constructor and move assignment operator added. We’ve left in the deep-copying copy constructor and copy assignment operator for comparison purposes.
~~~
#include <iostream>
 
template<class T>
class Auto_ptr4
{
	T* m_ptr;
public:
	Auto_ptr4(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}
 
	~Auto_ptr4()
	{
		delete m_ptr;
	}
 
	// Copy constructor
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4(const Auto_ptr4& a)
	{
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}
 
	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4(Auto_ptr4&& a) noexcept
		: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr; // we'll talk more about this line below
	}
 
	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr4& operator=(const Auto_ptr4& a)
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Copy the resource
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
 
		return *this;
	}
 
	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr4& operator=(Auto_ptr4&& a) noexcept
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr; // we'll talk more about this line below
 
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};
 
class Resource
{
public:
	Resource() { std::cout << "Resource acquired\n"; }
	~Resource() { std::cout << "Resource destroyed\n"; }
};
 
Auto_ptr4<Resource> generateResource()
{
	Auto_ptr4<Resource> res(new Resource);
	return res; // this return value will invoke the move constructor
}
 
int main()
{
	Auto_ptr4<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the move assignment
 
	return 0;
}
~~~
The move constructor and move assignment operator are simple. Instead of deep copying the source object (a) into the implicit object, we simply move (steal) the source object’s resources. This involves shallow copying the source pointer into the implicit object, then setting the source pointer to null.

When run, this program prints:
~~~
Resource acquired
Resource destroyed
~~~
That’s much better!

The flow of the program is exactly the same as before. However, instead of calling the copy constructor and copy assignment operators, this program calls the move constructor and move assignment operators. Looking a little more deeply:
~~~
1) Inside generateResource(), local variable res is created and initialized with a dynamically allocated Resource, which causes the first “Resource acquired”.
2) Res is returned back to main() by value. Res is move constructed into a temporary object, transferring the dynamically created object stored in res to the temporary object. We’ll talk about why this happens below.
3) Res goes out of scope. Because res no longer manages a pointer (it was moved to the temporary), nothing interesting happens here.
4) The temporary object is move assigned to mainres. This transfers the dynamically created object stored in the temporary to mainres.
5) The assignment expression ends, and the temporary object goes out of expression scope and is destroyed. However, because the temporary no longer manages a pointer (it was moved to mainres), nothing interesting happens here either.
6) At the end of main(), mainres goes out of scope, and our final “Resource destroyed” is displayed.
~~~
So instead of copying our Resource twice (once for the copy constructor and once for the copy assignment), we transfer it twice. This is more efficient, as Resource is only constructed and destroyed once instead of three times.

## When are the move constructor and move assignment called?

The move constructor and move assignment are called when those functions have been defined, and the argument for construction or assignment is an r-value. Most typically, this r-value will be a literal or temporary value.

In most cases, a move constructor and move assignment operator will not be provided by default, unless the class does not have any defined copy constructors, copy assignment, move assignment, or destructors. However, the default move constructor and move assignment do the same thing as the default copy constructor and copy assignment (make copies, not do moves).

Rule: If you want a move constructor and move assignment that do moves, you’ll need to write them yourself.

## The key insight behind move semantics

You now have enough context to understand the key insight behind move semantics.

If we construct an object or do an assignment where the argument is an l-value, the only thing we can reasonably do is copy the l-value. We can’t assume it’s safe to alter the l-value, because it may be used again later in the program. If we have an expression “a = b”, we wouldn’t reasonably expect b to be changed in any way.

However, if we construct an object or do an assignment where the argument is an r-value, then we know that r-value is just a temporary object of some kind. Instead of copying it (which can be expensive), we can simply transfer its resources (which is cheap) to the object we’re constructing or assigning. This is safe to do because the temporary will be destroyed at the end of the expression anyway, so we know it will never be used again!

C++11, through r-value references, gives us the ability to provide different behaviors when the argument is an r-value vs an l-value, enabling us to make smarter and more efficient decisions about how our objects should behave.

## Move functions should always leave both objects in a well-defined state

In the above examples, both the move constructor and move assignment functions set a.m_ptr to nullptr. This may seem extraneous -- after all, if “a” is a temporary r-value, why bother doing “cleanup” if parameter “a” is going to be destroyed anyway?

The answer is simple: When “a” goes out of scope, a’s destructor will be called, and a.m_ptr will be deleted. If at that point, a.m_ptr is still pointing to the same object as m_ptr, then m_ptr will be left as a dangling pointer. When the object containing m_ptr eventually gets used (or destroyed), we’ll get undefined behavior.

Additionally, in the next lesson we’ll see cases where “a” can be an l-value. In such a case, “a” wouldn’t be destroyed immediately, and could be queried further before its lifetime ends.

## Automatic l-values returned by value may be moved instead of copied

In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by value, it is moved instead of copied, even though res is an l-value. The C++ specification has a special rule that says automatic objects returned from a function by value can be moved even if they are l-values. This makes sense, since res was going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an expensive and unnecessary copy.

Although the compiler can move l-value return values, in some cases it may be able to do even better by simply eliding the copy altogether (which avoids the need to make a copy or do a move at all). In such a case, neither the copy constructor nor move constructor would be called.

## 1.3 Disabling copying
In the Auto_ptr4 class above, we left in the copy constructor and assignment operator for comparison purposes. But in move-enabled classes, it is sometimes desirable to delete the copy constructor and copy assignment functions to ensure copies aren’t made. In the case of our Auto_ptr class, we don’t want to copy our templated object T -- both because it’s expensive, and whatever class T is may not even support copying!

Here’s a version of Auto_ptr that supports move semantics but not copy semantics:
~~~

2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
#include <iostream>
 
template<class T>
class Auto_ptr5
{
	T* m_ptr;
public:
	Auto_ptr5(T* ptr = nullptr)
		:m_ptr(ptr)
	{
	}
 
	~Auto_ptr5()
	{
		delete m_ptr;
	}
 
	// Copy constructor -- no copying allowed!
	Auto_ptr5(const Auto_ptr5& a) = delete;
 
	// Move constructor
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5(Auto_ptr5&& a) noexcept
		: m_ptr(a.m_ptr)
	{
		a.m_ptr = nullptr;
	}
 
	// Copy assignment -- no copying allowed!
	Auto_ptr5& operator=(const Auto_ptr5& a) = delete;
 
	// Move assignment
	// Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5& operator=(Auto_ptr5&& a) noexcept
	{
		// Self-assignment detection
		if (&a == this)
			return *this;
 
		// Release any resource we're holding
		delete m_ptr;
 
		// Transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
 
		return *this;
	}
 
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }
};
~~~
If you were to try to pass an Auto_ptr5 l-value to a function by value, the compiler would complain that the copy constructor required to initialize the function argument has been deleted. This is good, because we should probably be passing Auto_ptr5 by const l-value reference anyway!

Auto_ptr5 is (finally) a good smart pointer class. And, in fact the standard library contains a class very much like this one (that you should use instead), named std::unique_ptr. We’ll talk more about std::unique_ptr later in this chapter.

### example
Let’s take a look at another class that uses dynamic memory: a simple dynamic templated array. This class contains a deep-copying copy constructor and copy assignment operator.
~~~
#include <iostream>
 
template <class T>
class DynamicArray
{
private:
	T* m_array;
	int m_length;
 
public:
	DynamicArray(int length)
		: m_array(new T[length]), m_length(length)
	{
	}
 
	~DynamicArray()
	{
		delete[] m_array;
	}
 
	// Copy constructor
	DynamicArray(const DynamicArray &arr)
		: m_length(arr.m_length)
	{
		m_array = new T[m_length];
		for (int i = 0; i < m_length; ++i)
			m_array[i] = arr.m_array[i];
	}
 
	// Copy assignment
	DynamicArray& operator=(const DynamicArray &arr)
	{
		if (&arr == this)
			return *this;
 
		delete[] m_array;
		
		m_length = arr.m_length;
		m_array = new T[m_length];
 
		for (int i = 0; i < m_length; ++i)
			m_array[i] = arr.m_array[i];
 
		return *this;
	}
 
	int getLength() const { return m_length; }
	T& operator[](int index) { return m_array[index]; }
	const T& operator[](int index) const { return m_array[index]; }
 
};
~~~
Now let’s use this class in a program. To show you how this class performs when we allocate a million integers on the heap, we’re going to leverage the Timer class we developed in lesson 12.18 -- Timing your code. We’ll use the Timer class to time how fast our code runs, and show you the performance difference between copying and moving.

~~~
#include <iostream>
#include <chrono> // for std::chrono functions
 
// Uses the above DynamicArray class
 
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
	
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now())
	{
	}
	
	void reset()
	{
		m_beg = clock_t::now();
	}
	
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
 
// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
{
	DynamicArray<int> dbl(arr.getLength());
	for (int i = 0; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;
 
	return dbl;
}
 
int main()
{
	Timer t;
 
	DynamicArray<int> arr(1000000);
 
	for (int i = 0; i < arr.getLength(); i++)
		arr[i] = i;
 
	arr = cloneArrayAndDouble(arr);
 
	std::cout << t.elapsed();
}
~~~

On one of the author’s machines, in release mode, this program executed in 0.00825559 seconds.

Now let’s run the same program again, replacing the copy constructor and copy assignment with a move constructor and move assignment.
~~~
template <class T>
class DynamicArray
{
private:
	T* m_array;
	int m_length;
 
public:
	DynamicArray(int length)
		: m_array(new T[length]), m_length(length)
	{
	}
 
	~DynamicArray()
	{
		delete[] m_array;
	}
 
	// Copy constructor
	DynamicArray(const DynamicArray &arr) = delete;
 
	// Copy assignment
	DynamicArray& operator=(const DynamicArray &arr) = delete;
 
	// Move constructor
	DynamicArray(DynamicArray &&arr) noexcept
		: m_length(arr.m_length), m_array(arr.m_array)
	{
		arr.m_length = 0;
		arr.m_array = nullptr;
	}
 
	// Move assignment
	DynamicArray& operator=(DynamicArray &&arr) noexcept
	{
		if (&arr == this)
			return *this;
 
		delete[] m_array;
 
		m_length = arr.m_length;
		m_array = arr.m_array;
		arr.m_length = 0;
		arr.m_array = nullptr;
 
		return *this;
	}
 
	int getLength() const { return m_length; }
	T& operator[](int index) { return m_array[index]; }
	const T& operator[](int index) const { return m_array[index]; }
 
};
 
#include <iostream>
#include <chrono> // for std::chrono functions
 
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
 
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now())
	{
	}
 
	void reset()
	{
		m_beg = clock_t::now();
	}
 
	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};
 
// Return a copy of arr with all of the values doubled
DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
{
	DynamicArray<int> dbl(arr.getLength());
	for (int i = 0; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;
 
	return dbl;
}
 
int main()
{
	Timer t;
 
	DynamicArray<int> arr(1000000);
 
	for (int i = 0; i < arr.getLength(); i++)
		arr[i] = i;
 
	arr = cloneArrayAndDouble(arr);
 
	std::cout << t.elapsed();
}
~~~
On the same machine, this program executed in 0.0056 seconds.

Comparing the runtime of the two programs, 0.0056 / 0.00825559 = 67.8%. The move version was almost 33% faster!


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
	
https://www.learncpp.com/cpp-tutorial/intro-to-smart-pointers-move-semantics/	
	
https://www.internalpointers.com/post/beginner-s-look-smart-pointers-modern-c
 
