#include <iostream>
using namespace std;


int main(){
    // 1数组的声明 array declaration syntax: type arrayName [ arraySize];
    int my_array[10];
    //double array[];  //without size

    // 2数组的声明+初始化
    double balance[5] = {1000.0,2.2,3.3,7.9,50.5};

    int bal[] = {1,2,3}; // 如果您省略掉了数组的大小，数组的大小则为初始化时元素的个数

    // 3访问数组元素
    cout << bal[2] << endl;

    // 4插入元素
    my_array[0] = 123;

    // 5遍历数组： 2中方法遍历
    for(int i=0; i<3;i++){
        cout << balance[i] << endl;
    
    }

    // 使用指针遍历数组
    // 特殊: cpp中的数组对象本身是一个内存地址
    for(int* p=bal;p<bal+3;p++){
        cout << *p << endl;
    }
    return 0;
}
