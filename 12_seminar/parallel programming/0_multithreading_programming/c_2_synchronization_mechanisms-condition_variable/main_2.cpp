#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> shared_queue; // 共享队列
std::mutex mtx; // 互斥锁
std::condition_variable cv_producer, cv_consumer; // 条件变量
const int MAX_QUEUE_SIZE = 5; // 队列最大容量

// 生产者任务
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // 如果队列已满，等待消费者消费
        cv_producer.wait(lock, [] { return shared_queue.size() < MAX_QUEUE_SIZE; });

        // 生产数据
        shared_queue.push(i);
        std::cout << "Producer " << id << " produced: " << i << std::endl;

        // 通知消费者
        cv_consumer.notify_one();
    }
}

// 消费者任务
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lock(mtx);

        // 如果队列为空，等待生产者生产
        cv_consumer.wait(lock, [] { return !shared_queue.empty(); });

        // 消费数据
        int data = shared_queue.front();
        shared_queue.pop();
        std::cout << "Consumer " << id << " consumed: " << data << std::endl;

        // 通知生产者
        cv_producer.notify_one();
    }
}

int main() {
    std::thread producers[2];
    std::thread consumers[2];

    // 创建生产者线程
    for (int i = 0; i < 2; ++i) {
        producers[i] = std::thread(producer, i + 1);
    }

    // 创建消费者线程
    for (int i = 0; i < 2; ++i) {
        consumers[i] = std::thread(consumer, i + 1);
    }

    // 等待生产者线程完成
    for (int i = 0; i < 2; ++i) {
        producers[i].join();
    }

    // 等待消费者线程完成
    for (int i = 0; i < 2; ++i) {
        consumers[i].join();
    }

    return 0;
}