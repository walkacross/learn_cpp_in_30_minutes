#include <iostream>
#include <stack>
using namespace std;

int main(){

    // declaration stack: stack<object_type> stack_name;
    stack<int> s;

    // insert element
    s.push(2);
    s.push(3);

    // top function
    cout << s.top() << endl;

    // size and empty function
    cout << s.size() << s.empty() << endl;

    // pop This method is used to removes single element from the stack. It reduces the size of the stack by 1. The element removed is always the topmost element of the stack (most recently added element) . The pop() method does not return anything.
    s.pop();

    return 0;

}
