#include <iostream>
#include <queue>
using namespace std;


int main(){

    // declaration: queue< object_type >  queue_name;
    queue<int> q;
    
    // push function
    q.push(2);
    q.push(3);

    // pop funtion: This method removes single element from the front of the queue and therefore reduces its size by 1. The element removed is the element that was entered first. the pop() does not return anything.
    q.pop();
    cout << q.size() << endl;

    return 0;
}
