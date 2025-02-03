#include <iostream>
#include <vector>
using namespace std;

// https://www.studytonight.com/cpp/stl/stl-container-vector
// https://www.runoob.com/w3cnote/cpp-vector-container-analysis.html
//
int main(){

    // 1declaration creation: vector< object_type > vector_name;
    vector<int> my_vector;

    // 2声明+初始化
    vector<string> v {"yujiang","allen","code","python"};

    // 3访问容器中的元素 []operator == .at 方法
    cout << v[0] << endl;
    cout << v.at(1) << endl;

    // 4向容器中插入元素
    // 4.1
    v.push_back("cpp");    // push_back向容器尾部添加元素
    // 4.2 insert(itr, element) method inserts the element in vector before the position pointed by iterator itr.
    vector<string>::iterator i = v.begin();
    v.insert(i,"cpp");
    
    // 5 遍历容器
    // 5.1 for循环
    for(int i=0;i<v.size();i++){
        cout << v[i] << endl;
    }
    // 5.2 for+iterator(指针)遍历
    vector<string>::iterator it;
    for(it = v.begin();it != v.end(); it++){
        cout << *it << endl;
    }

    return 0;
}
