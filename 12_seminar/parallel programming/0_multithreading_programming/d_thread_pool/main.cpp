#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <string>

class ThreadPool {
public:
    ThreadPool(size_t numThreads) : stop(false) {
        for (size_t i = 0; i < numThreads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        if (this->stop && this->tasks.empty()) return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    template<class F, class... Args>
    void enqueue(F&& f, Args&&... args) {
        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            tasks.emplace([task] { task(); });
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread &worker : workers)
            worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

// Function with multiple parameters
void processTask(int taskId, const std::string& message, double value) {
    std::cout << "Starting task " << taskId 
              << " (" << message << ", " << value << ")"
              << " on thread " << std::this_thread::get_id() << std::endl;
    
    // Simulate work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    std::cout << "Completed task " << taskId 
              << " (" << message << ", " << value << ")"
              << " on thread " << std::this_thread::get_id() << std::endl;
}

int main() {
    // Create thread pool with 4 worker threads
    ThreadPool pool(4);

    // Enqueue tasks with different parameters
    for (int i = 0; i < 8; ++i) {
        pool.enqueue(processTask, 
                    i,                               // taskId
                    "Task description",              // message
                    static_cast<double>(i) * 3.14);  // value
    }

    // Allow time for all tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}