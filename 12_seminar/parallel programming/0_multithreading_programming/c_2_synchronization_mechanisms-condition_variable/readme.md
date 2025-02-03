### Motivation for `std::condition_variable`

In multithreaded programming, threads often need to wait for specific conditions to be met before proceeding. Busy-waiting (e.g., looping and polling) is inefficient and wastes CPU cycles. **`std::condition_variable`** solves this by allowing threads to **block and wait** until a condition is signaled by another thread. It works with **mutexes** to safely coordinate access to shared data and avoid race conditions.

#### Key Motivations:
1. **Avoid Busy-Waiting**: Threads sleep until notified, saving CPU resources.
2. **Synchronization**: Coordinate threads to act only when specific conditions are met.
3. **Efficiency**: Reduce contention and unnecessary CPU usage.
4. **Predicate Safety**: Handle spurious wakeups (threads waking up without a true condition change).

---

### Complexity Examples Illustrating `std::condition_variable`

#### Example 1: Simple Producer-Consumer (1 Producer, 1 Consumer)
**Scenario**: A producer generates data, and a consumer processes it when available.  
**Why Use `condition_variable`**: The consumer should wait efficiently instead of polling.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> data_queue;

void producer() {
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_one(); // Notify the waiting consumer
    }
}

void consumer() {
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until the queue is not empty
        cv.wait(lock, [] { return !data_queue.empty(); });
        int data = data_queue.front();
        data_queue.pop();
        std::cout << "Consumed: " << data << std::endl;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
```

**Explanation**:
- The consumer waits using `cv.wait(lock, predicate)`, which blocks until `notify_one()` is called and the queue is non-empty.
- The predicate `[] { return !data_queue.empty(); }` prevents spurious wakeups.

---

#### Example 2: Multiple Producers and Consumers (2 Producers, 3 Consumers)
**Scenario**: Multiple producers add data to a shared queue, and multiple consumers process it.  
**Why Use `condition_variable`**: Coordinate multiple threads to safely share a resource.

```cpp
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
```

**Explanation**:
- Multiple producers add data to the queue, and multiple consumers process it.
- `cv.notify_all()` wakes up all waiting consumers to check the queue.

---

#### Example 3: Thread Pool with Task Queue
**Scenario**: A thread pool where worker threads wait for tasks to be added to a queue.  
**Why Use `condition_variable`**: Workers block until tasks are available.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
std::queue<std::function<void()>> task_queue;
bool stop_pool = false;

void worker(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !task_queue.empty() || stop_pool; });
        if (stop_pool && task_queue.empty()) break;
        auto task = task_queue.front();
        task_queue.pop();
        lock.unlock();
        std::cout << "Worker " << id << " executing task\n";
        task(); // Execute the task
    }
}

int main() {
    std::vector<std::thread> workers;
    for (int i = 0; i < 4; ++i) {
        workers.emplace_back(worker, i+1);
    }

    // Add tasks to the queue
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            task_queue.push([i] { std::cout << "Task " << i << " done\n"; });
        }
        cv.notify_one();
    }

    // Stop the thread pool
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop_pool = true;
    }
    cv.notify_all();

    for (auto& t : workers) t.join();
    return 0;
}
```

**Explanation**:
- Worker threads wait for tasks using `cv.wait()`.
- The main thread adds tasks and notifies workers with `cv.notify_one()` or `cv.notify_all()`.

---

#### Example 4: Complex Synchronization with Predicates
**Scenario**: A thread waits for multiple conditions (e.g., a counter reaching a threshold).  
**Why Use `condition_variable`**: Safely handle complex conditions and spurious wakeups.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int counter = 0;
const int TARGET = 5;

void incrementer() {
    for (int i = 0; i < TARGET; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(mtx);
            ++counter;
            std::cout << "Counter: " << counter << std::endl;
        }
        cv.notify_all(); // Notify all waiting threads
    }
}

void waiter() {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until counter reaches TARGET
    cv.wait(lock, [] { return counter >= TARGET; });
    std::cout << "Counter reached target (" << TARGET << ")!\n";
}

int main() {
    std::thread t1(incrementer);
    std::thread t2(waiter);
    t1.join();
    t2.join();
    return 0;
}
```

**Explanation**:
- The waiter thread blocks until `counter >= TARGET` using a predicate.
- The predicate ensures the thread only proceeds when the condition is truly met.

---

### Key Takeaways
1. **Efficiency**: Threads block instead of busy-waiting.
2. **Safety**: Predicates prevent spurious wakeups (e.g., `cv.wait(lock, predicate)`).
3. **Flexibility**: Coordinate multiple threads with shared conditions.
4. **Use Cases**: Producer-consumer patterns, thread pools, complex synchronization logic.

By using `std::condition_variable`, you can build efficient, thread-safe applications that avoid resource contention and unnecessary CPU usage.