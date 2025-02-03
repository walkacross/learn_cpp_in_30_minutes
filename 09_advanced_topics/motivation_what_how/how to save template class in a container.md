# how to save template class in a container ?
> https://stackoverflow.com/questions/39105623/storing-classes-inherited-of-a-class-template-in-a-c-vector

> https://stackoverflow.com/questions/16527673/c-one-stdvector-containing-template-class-of-multiple-types

First, you could define a common non template ancestor:
~~~
class MyCommonAncestor {
public:  
    virtual void common_operation1()=0;
    virtual ~MyCommonAncestor() {}
}; 

template <class X, class Y> 
class MyTemplateClass : public MyCommonAncestor {
    X myx; 
    Y myY; 
public:  
    void common_operation1() override; 
    X operation2(const Y& y); 
};
~~~

Unfortunately, doing so doesn't really allow you to use a vector<MyCommonAncestor> because such a vector would hold MyCommonAncestor objects only (which can't be created because they have a pure virtual function here) and if they could be created, they would slice the derived objects that you'd put in (i.e. they risk to loose myX and myY).

### Challenges

A challenge occurs when you want to call a function that depends on the template parameters (example operation2()). Obviously, these can't be included in the common ancestor, as they depend on template paramters which are not yet defined.

Possible workarounds:

* avoid these, and call such functions only indirectly via common operations (which can be overridden in the template)
* use in the common interfaces abstract types for parameters. Pass these by pointer or by reference. Later, for A and B or U and V, make sure that these are derived from the intended abstract types.
~~~
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
 
struct A { void what_type() { cout<<"A"<<endl; }};
struct B { void what_type() { cout<<"B"<<endl; }};
struct U { void what_type() { cout<<"U"<<endl; }};
struct V { void what_type() { cout<<"V"<<endl; }};
 
class MyCommonAncestor {
public:  
    virtual void common_operation1()=0;
    virtual ~MyCommonAncestor() {}
}; 
 
template <class X, class Y> 
class MyTemplateClass : public MyCommonAncestor {
    X myx; 
    Y myY; 
public:  
    void common_operation1() override {  // addresses specific objects of type X and Y
    	myx.what_type();
    	myY.what_type();
    }; 
    X operation2(const Y& y) {}; 
    ~MyTemplateClass() {   // to demonstrate automatic destruction for shared ptr
    	cout<<"object destroyed"<<endl;
    } 
};
 
int main() {
	vector<shared_ptr<MyCommonAncestor>> myVector; 
	myVector.push_back(make_shared<MyTemplateClass<A,B>>()); 
	myVector.push_back(make_shared<MyTemplateClass<U,V>>()); 
	for (auto& x: myVector)
	    x->common_operation1(); 
	return 0;
}
~~~

~~~
A
B
U
V
object destroyed
object destroyed
~~~
