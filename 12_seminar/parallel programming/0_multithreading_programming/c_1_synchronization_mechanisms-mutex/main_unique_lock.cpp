#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <string>
#include <mutex>

// Global shared list
std::list<std::string> shared_list;

// Mutex to protect the shared list
std::mutex mtx;

// Simulate matrix multiplication (generates 3 data entries)
void matrixMultiplication(int durationInSeconds = 3) {
    std::cout << "Matrix multiplication started, thread ID: " 
              << std::this_thread::get_id() << std::endl;
    
    for (int i = 0; i < durationInSeconds; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Use std::unique_lock to lock the mutex
        std::unique_lock<std::mutex> lock(mtx);
        shared_list.push_back("Matrix result step " + std::to_string(i+1));
        
        std::cout << "Matrix multiplication added data: Step " << (i+1) << std::endl;
        
        // Lock is automatically released when `lock` goes out of scope
    }
    std::cout << "Matrix multiplication completed!" << std::endl;
}

// Simulate image processing (generates 2 data entries)
void imageProcessing() {
    std::cout << "Image processing started, thread ID: " 
              << std::this_thread::get_id() << std::endl;
    
    for (int i = 0; i < 2; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Use std::unique_lock to lock the mutex
        std::unique_lock<std::mutex> lock(mtx);
        shared_list.push_back("Image processed " + std::to_string(i+1));
        
        std::cout << "Image processing added data: Image " << (i+1) << std::endl;
        
        // Lock is automatically released when `lock` goes out of scope
    }
    std::cout << "Image processing completed!" << std::endl;
}

// Simulate scientific computation (generates 4 data entries)
void scientificComputation(int durationInSeconds = 4) {
    std::cout << "Scientific computation started, thread ID: " 
              << std::this_thread::get_id() << std::endl;
    
    for (int i = 0; i < durationInSeconds; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Use std::unique_lock to lock the mutex
        std::unique_lock<std::mutex> lock(mtx);
        shared_list.push_back("Science data #" + std::to_string(i+1));
        
        std::cout << "Scientific computation added data: Data #" << (i+1) << std::endl;
        
        // Lock is automatically released when `lock` goes out of scope
    }
    std::cout << "Scientific computation completed!" << std::endl;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    // Create 3 threads to perform different tasks
    std::thread t1(matrixMultiplication, 3);
    std::thread t2(imageProcessing);
    std::thread t3(scientificComputation, 4);

    std::cout << "Main thread is waiting for sub-threads..." << std::endl;

    // Wait for all threads to complete
    t1.join();
    t2.join();
    t3.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output all collected data
    std::cout << "\nCollected data (" << shared_list.size() << " items):\n";
    for (const auto& item : shared_list) {
        std::cout << " - " << item << std::endl;
    }

    // Output total execution time
    std::cout << "\nAll tasks completed in " << elapsed.count() 
              << " seconds." << std::endl;

    return 0;
}