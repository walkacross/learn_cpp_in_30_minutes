#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // 定义互斥锁
int shared_value = 0; // 共享资源

void task(int id) {
    for (int i = 0; i < 5; ++i) {
        mtx.lock(); // 手动加锁
        shared_value += 1; // 修改共享资源
        std::cout << "Thread " << id << ": shared_value = " << shared_value << std::endl;
        mtx.unlock(); // 手动解锁
    }
}

int main() {
    std::thread t1(task, 1);
    std::thread t2(task, 2);

    t1.join();
    t2.join();

    std::cout << "Final shared_value: " << shared_value << std::endl;
    return 0;
}