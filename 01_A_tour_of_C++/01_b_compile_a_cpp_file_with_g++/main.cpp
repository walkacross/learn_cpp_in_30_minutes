#include <iostream>
#include "hello.h"

int main(){
    int val = hello();
    std::cout << "the return value is: " << val << std::endl;
    return 0;
}
