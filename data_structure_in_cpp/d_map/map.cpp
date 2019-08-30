#include <iostream>
#include <map>
using namespace std;

int main(){

    // 1 declaration: map<key_type , value_type> map_name;
    map<string,int> map1;
    map1["abc"] = 300;
    map1["b"] = 100;
    map1["def"] = 250;

    // 2 declaration + 初始化
    map<string,int> map2{{"a",100},{"b",200},{"c",300}};

    // 3 访问容器元素 []operator == .at() method
    cout << map1["abc"] << endl;
    cout << map1["def"] << endl;

    // 4 向容器中插入元素
    // insert(pair) : In this variation, a pair of key and value is inserted in the map. The inserted pair is always inserted at the appropriate position as keys are arranged in sorted order.
    map1.insert(pair<string,int> ("d",500));
    map1.insert(make_pair("e",700));

    // 5遍历容器
    map<string,int>::iterator iter;
    for(iter=map1.begin(); iter != map1.end(); iter++){
        cout << iter->first << ":" << iter->second << endl;
    }

    return 0;

}


