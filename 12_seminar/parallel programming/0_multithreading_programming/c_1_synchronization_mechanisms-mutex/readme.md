### Basic Knowledge of How to Use Mutex

A **mutex** (short for "mutual exclusion") is a synchronization primitive used to protect shared resources from concurrent access by multiple threads. It ensures that only one thread can access a critical section of code at a time, preventing race conditions and data corruption.

---

### 1. **What is a Mutex?**
- A mutex is a lock that threads must acquire before accessing a shared resource.
- If one thread holds the lock, other threads attempting to acquire it will block until the lock is released.

---

### 2. **Why Use a Mutex?**
- **Prevent Race Conditions**: Ensures that only one thread can modify shared data at a time.
- **Ensure Thread Safety**: Protects critical sections of code from concurrent access.
- **Avoid Data Corruption**: Prevents inconsistent or invalid states in shared resources.

---

### 3. **How to Use a Mutex in C++**

In C++, the `std::mutex` class (defined in the `<mutex>` header) is used to implement mutexes. Here's a step-by-step guide:

#### a) **Include the Required Header**
```cpp
#include <mutex>
```

#### b) **Declare a Mutex**
Declare a `std::mutex` object to protect the shared resource.
```cpp
std::mutex mtx;
```

#### c) **Lock the Mutex**
Use the `lock()` method to acquire the mutex before accessing the shared resource.
```cpp
mtx.lock();
```

#### d) **Unlock the Mutex**
Use the `unlock()` method to release the mutex after accessing the shared resource.
```cpp
mtx.unlock();
```

#### e) **Use `std::lock_guard` for Automatic Lock Management**
To avoid manually calling `lock()` and `unlock()`, use `std::lock_guard`. It automatically locks the mutex when created and unlocks it when destroyed (RAII principle).
```cpp
std::lock_guard<std::mutex> lock(mtx);
```

---

### 4. **Example: Using Mutex to Protect a Shared Counter**

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Shared resource
int shared_counter = 0;

// Mutex to protect the shared resource
std::mutex mtx;

void increment_counter(int id) {
    for (int i = 0; i < 1000; ++i) {
        // Lock the mutex before accessing the shared resource
        std::lock_guard<std::mutex> lock(mtx);
        shared_counter++; // Safely modify the shared resource
    }
    std::cout << "Thread " << id << " finished.\n";
}

int main() {
    std::vector<std::thread> threads;

    // Create 10 threads to increment the shared counter
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment_counter, i);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Output the final value of the shared counter
    std::cout << "Final counter value: " << shared_counter << std::endl;

    return 0;
}
```

#### Explanation:
- **Shared Resource**: `shared_counter` is accessed by multiple threads.
- **Mutex**: `std::mutex mtx` protects the critical section (`shared_counter++`).
- **Lock Management**: `std::lock_guard` ensures the mutex is automatically locked and unlocked.

---

### 5. **Common Mutex Operations**

#### a) **Manual Locking and Unlocking**
```cpp
mtx.lock();   // Acquire the lock
// Critical section
mtx.unlock(); // Release the lock
```

#### b) **Using `std::lock_guard`**
```cpp
{
    std::lock_guard<std::mutex> lock(mtx); // Automatically locks the mutex
    // Critical section
} // Automatically unlocks the mutex when the lock_guard goes out of scope
```

#### c) **Using `std::unique_lock`**
`std::unique_lock` provides more flexibility than `std::lock_guard` (e.g., deferred locking, manual unlocking).
```cpp
std::unique_lock<std::mutex> lock(mtx);
// Critical section
lock.unlock(); // Manually unlock if needed
```

---

### 6. **Best Practices for Using Mutex**

#### a) **Minimize Lock Duration**
- Hold the lock only for the duration of the critical section to avoid blocking other threads unnecessarily.

#### b) **Avoid Deadlocks**
- Always acquire locks in a consistent order.
- Use `std::lock` to lock multiple mutexes simultaneously without deadlocks.

#### c) **Use RAII Wrappers**
- Prefer `std::lock_guard` or `std::unique_lock` over manual `lock()` and `unlock()` calls to ensure the mutex is always released.

#### d) **Avoid Nested Locks**
- Nesting locks can lead to deadlocks. If you must nest locks, use `std::recursive_mutex`.

#### e) **Test for Thread Safety**
- Use tools like **ThreadSanitizer** to detect race conditions and deadlocks.

---

### 7. **Advanced Mutex Types**

#### a) **`std::recursive_mutex`**
- Allows the same thread to lock the mutex multiple times without deadlocking.
- Useful for recursive functions or nested critical sections.

#### b) **`std::timed_mutex`**
- Supports timeouts for locking attempts.
- Methods: `try_lock_for()`, `try_lock_until()`.

#### c) **`std::shared_mutex`**
- Supports shared (read-only) and exclusive (write) locking.
- Use `std::shared_lock` for shared access and `std::unique_lock` for exclusive access.


### 8. **Conclusion**
- A mutex is a fundamental tool for ensuring thread safety in multi-threaded programs.
- Use `std::mutex` to protect shared resources and avoid race conditions.
- Prefer RAII wrappers like `std::lock_guard` or `std::unique_lock` for safe and clean lock management.
- Follow best practices to minimize lock contention, avoid deadlocks, and ensure efficient concurrent execution.


# command
~~~
g++ -o main_mannual_lock main_mannual_lock.cpp -lpthread
~~~

~~~
g++ -o main_lock_guard main_lock_guard.cpp -lpthread
~~~

# appendix
Basic Knowledge and Overview of std::unique_lock
std::unique_lock is a more flexible and powerful alternative to std::lock_guard for managing mutexes in C++. It provides additional features like deferred locking, manual locking/unlocking, and the ability to transfer ownership of the lock. It is part of the C++ Standard Library and is defined in the <mutex> header.

1. What is std::unique_lock?
std::unique_lock is a RAII (Resource Acquisition Is Initialization) wrapper for managing mutex locks.

It allows you to lock and unlock a mutex in a more flexible way compared to std::lock_guard.

It can be used with any lockable object, such as std::mutex, std::timed_mutex, or std::recursive_mutex.

2. Why Use std::unique_lock?
Flexibility: Supports deferred locking, manual locking/unlocking, and try-lock operations.

Transferability: Ownership of the lock can be transferred between std::unique_lock instances.

Compatibility: Works with condition variables (std::condition_variable), which require the ability to manually unlock a mutex.

3. Key Features of std::unique_lock
a) Deferred Locking
The mutex is not locked immediately when the std::unique_lock is created. Instead, you can lock it later using the lock() method.

b) Manual Locking/Unlocking
You can manually lock and unlock the mutex using the lock() and unlock() methods.

c) Try-Lock
You can attempt to lock the mutex without blocking using the try_lock() method.

d) Ownership Transfer
Ownership of the lock can be transferred to another std::unique_lock instance using move semantics.

e) RAII Guarantee
Like std::lock_guard, std::unique_lock automatically releases the lock when it goes out of scope.

4. How to Use std::unique_lock
a) Basic Usage
cpp
Copy
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    std::cout << "Thread ID: " << std::this_thread::get_id() << " is running.\n";
    // Lock is automatically released when `lock` goes out of scope
}

int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    return 0;
}
b) Deferred Locking
cpp
Copy
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Defer locking
    std::cout << "Thread ID: " << std::this_thread::get_id() << " is running.\n";
    lock.lock(); // Manually lock the mutex
    // Critical section
    lock.unlock(); // Manually unlock the mutex
}
c) Manual Locking/Unlocking
cpp
Copy
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    std::cout << "Thread ID: " << std::this_thread::get_id() << " is running.\n";
    lock.unlock(); // Manually unlock the mutex
    // Do other work
    lock.lock(); // Manually lock the mutex again
    // Critical section
}
d) Try-Lock
cpp
Copy
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    if (lock.try_lock()) { // Try to lock the mutex
        std::cout << "Thread ID: " << std::this_thread::get_id() << " acquired the lock.\n";
        // Critical section
    } else {
        std::cout << "Thread ID: " << std::this_thread::get_id() << " failed to acquire the lock.\n";
    }
}
e) Transfer Ownership
cpp
Copy
void threadFunction(std::unique_lock<std::mutex> lock) {
    std::cout << "Thread ID: " << std::this_thread::get_id() << " is running.\n";
    // Critical section
}

int main() {
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx); // Lock the mutex
    std::thread t(threadFunction, std::move(lock)); // Transfer ownership
    t.join();
    return 0;
}
