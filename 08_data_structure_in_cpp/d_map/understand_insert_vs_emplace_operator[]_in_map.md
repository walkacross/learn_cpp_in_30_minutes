# understand the difference insert, emplace_operator [] in map

> I'm using maps for the first time and I realized that there are many ways to insert an element. You can use emplace(), operator[] or insert(), plus variants like using value_type or make_pair. While there is a lot of information about all of them and questions about particular cases, I still can't understand the big picture. So, my two questions are:

> (1)What is the advantage of each one of them over the others?  (2)Was there any need for adding emplace to the standard? Is there anything that wasn't possible before without it?

> https://stackoverflow.com/questions/17172080/insert-vs-emplace-vs-operator-in-c-map

Emplace: Takes advantage of the rvalue reference to use the actual objects that you have already created. This means that no copy or move constructor is called, good for LARGE objects! O(log(N)) time.

Insert: Has overloads for standard lvalue reference and rvalue reference, as well as iterators to lists of elements to insert, and "hints" as to the position an element belongs. The use of a "hint" iterator can bring the time insertion takes down to contant time, otherwise it is O(log(N)) time.

Operator[]: Checks to see if the object exists, and if it does, modifies the reference to this object, otherwise uses the provided key and value to call make_pair on the two objects, and then does the same work as the insert function. This is O(log(N)) time.

make_pair: Does little more than make a pair.


The following code may help you understand the "big picture idea" of how insert() differs from emplace().

Summary of code: The Foo class uses static int foo_counter keeps track of the total number of Foo objects that have been constructed/moved thus far. Each Foo object also stores the value of foo_counter (at the time of its creation) in the local variable int val; if val is 8 then the Foo object will be called "foo8" or "Foo 8", etc. Every time a Foo constructor is called, it outputs info about the call to stdout (e.g. calling Foo(11) will output "Foo(int) with val: 11"). The code in main() prints to stdout the statement that will be executed (e.g. umap.emplace(11, d)) and then executes it.
~~~
#include <iostream>
#include <unordered_map>
#include <utility>

//Foo simply outputs what constructor is called with what value.
struct Foo {
  static int foo_counter; //Track how many Foo objects have been created.
  int val; //This Foo object was the val-th Foo object to be created.

  Foo() { val = foo_counter++;
    std::cout << "Foo() with val:                " << val << '\n';
  }
  Foo(int value) : val(value) { foo_counter++;
    std::cout << "Foo(int) with val:             " << val << '\n';
  }
  Foo(Foo& f2) { val = foo_counter++;
    std::cout << "Foo(Foo &) with val:           " << val
              << " \tcreated from:      \t" << f2.val << '\n';
  }
  Foo(const Foo& f2) { val = foo_counter++;
    std::cout << "Foo(const Foo &) with val:     " << val
              << " \tcreated from:      \t" << f2.val << '\n';
  }
  Foo(Foo&& f2) { val = foo_counter++;
    std::cout << "Foo(Foo&&) moving:             " << f2.val
              << " \tand changing it to:\t" << val << '\n';
  }
  ~Foo() { std::cout << "~Foo() destroying:             " << val << '\n'; }

  Foo& operator=(const Foo& rhs) {
    std::cout << "Foo& operator=(const Foo& rhs) with rhs.val: " << rhs.val
              << " \tcalled with lhs.val = \t" << val
              << " \tChanging lhs.val to: \t" << rhs.val << '\n';
    val = rhs.val;
    return *this;
  }

  bool operator==(const Foo &rhs) const { return val == rhs.val; }
  bool operator<(const Foo &rhs)  const { return val < rhs.val;  }
};

int Foo::foo_counter = 0;

//Create a hash function for Foo in order to use Foo with unordered_map
namespace std {
   template<> struct hash<Foo> {
       std::size_t operator()(const Foo &f) const {
           return std::hash<int>{}(f.val);
       }
   };
}

int main()
{
    std::unordered_map<Foo, int> umap;
    int d; //Some int that will be umap's value. It is not important.

    //Print the statement to be executed and then execute it.

    std::cout << "\nFoo foo0, foo1, foo2, foo3;\n";
    Foo foo0, foo1, foo2, foo3;

    std::cout << "\numap.insert(std::pair<Foo, int>(foo0, d))\n";
    umap.insert(std::pair<Foo, int>(foo0, d));
    //Side note: equiv. to: umap.insert(std::make_pair(foo0, d));

    std::cout << "\numap.insert(std::move(std::pair<Foo, int>(foo1, d)))\n";
    umap.insert(std::move(std::pair<Foo, int>(foo1, d)));
    //Side note: equiv. to: umap.insert(std::make_pair(foo1, d));
    
    std::cout << "\nstd::pair<Foo, int> pair(foo2, d)\n";
    std::pair<Foo, int> pair(foo2, d);

    std::cout << "\numap.insert(pair)\n";
    umap.insert(pair);

    std::cout << "\numap.emplace(foo3, d)\n";
    umap.emplace(foo3, d);
    
    std::cout << "\numap.emplace(11, d)\n";
    umap.emplace(11, d);

    std::cout << "\numap.insert({12, d})\n";
    umap.insert({12, d});

    std::cout.flush();
}
~~~

the output 
~~~
Foo foo0, foo1, foo2, foo3;
Foo() with val:                0
Foo() with val:                1
Foo() with val:                2
Foo() with val:                3

umap.insert(std::pair<Foo, int>(foo0, d))
Foo(Foo &) with val:           4    created from:       0
Foo(Foo&&) moving:             4    and changing it to: 5
~Foo() destroying:             4

umap.insert(std::move(std::pair<Foo, int>(foo1, d)))
Foo(Foo &) with val:           6    created from:       1
Foo(Foo&&) moving:             6    and changing it to: 7
~Foo() destroying:             6

std::pair<Foo, int> pair(foo2, d)
Foo(Foo &) with val:           8    created from:       2

umap.insert(pair)
Foo(const Foo &) with val:     9    created from:       8

umap.emplace(foo3, d)
Foo(Foo &) with val:           10   created from:       3

umap.emplace(11, d)
Foo(int) with val:             11

umap.insert({12, d})
Foo(int) with val:             12
Foo(const Foo &) with val:     13   created from:       12
~Foo() destroying:             12

~Foo() destroying:             8
~Foo() destroying:             3
~Foo() destroying:             2
~Foo() destroying:             1
~Foo() destroying:             0
~Foo() destroying:             13
~Foo() destroying:             11
~Foo() destroying:             5
~Foo() destroying:             10
~Foo() destroying:             7
~Foo() destroying:             9
~~~

This code and its output shows what the main "big picture" difference between insert() and emplace() is:

Whereas using insert() almost always requires the construction or pre-existence of some Foo object in main()'s scope (followed by a copy or move), if using emplace() then any call to a Foo constructor is done entirely internally in the unordered_map (i.e. inside the scope of the emplace() method's definition). The argument(s) for the key that you pass to emplace() are directly forwarded to a Foo constructor call within unordered_map::emplace()'s definition (optional additional details: where this newly constructed object is immediately incorporated into one of unordered_map's member variables so that no destructor is called when execution leaves emplace() and no move or copy constructors are called).
