#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;
const int MAX_ITEMS = 10;

void producer(int id) {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100 * id));
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (data_queue.size() < MAX_ITEMS) {
                data_queue.push(i);
                std::cout << "Producer " << id << " produced: " << i << std::endl;
            }
        }
        cv.notify_all(); // Notify all waiting consumers
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !data_queue.empty(); });
        int data = data_queue.front();
        data_queue.pop();
        std::cout << "Consumer " << id << " consumed: " << data << std::endl;
        lock.unlock();
        if (data == 4) break; // Exit condition
    }
}

int main() {
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);
    std::thread c3(consumer, 3);
    p1.join(); p2.join(); c1.join(); c2.join(); c3.join();
    return 0;
}