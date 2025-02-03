#include <iostream>
#include <thread>
#include <chrono>

// 模拟矩阵乘法
void matrixMultiplication(int durationInSeconds = 3) {
    std::cout << "Matrix multiplication started, started by thread ID: " << std::this_thread::get_id() << std::endl;
    // 模拟计算耗时
    for (int i = 0; i < durationInSeconds; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Matrix multiplication in progress..." << std::endl;
    }
    std::cout << "Matrix multiplication completed!" << std::endl;
}

// 模拟图像处理
void imageProcessing() {
    std::cout << "Image processing started, started by thread ID: " << std::this_thread::get_id() << std::endl;
    // 模拟图像处理耗时
    for (int i = 0; i < 2; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Image processing in progress..." << std::endl;
    }
    std::cout << "Image processing completed!" << std::endl;
}

// 模拟科学计算
void scientificComputation(int durationInSeconds = 4) {
    std::cout << "Scientific computation started, started by thread ID: " << std::this_thread::get_id() << std::endl;
    // 模拟科学计算耗时
    for (int i = 0; i < durationInSeconds; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Scientific computation in progress..." << std::endl;
    }
    std::cout << "Scientific computation completed!" << std::endl;
}

int main() {
    // 记录开始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 创建 3 个子线程，分别执行不同的任务
    std::thread t1(matrixMultiplication, 3);
    std::thread t2(imageProcessing);
    std::thread t3(scientificComputation, 4);

    // 主线程只负责创建和管理子线程
    std::cout << "Main thread is waiting for sub-threads to complete..." << std::endl;

    // 等待所有子线程完成
    t1.join();
    t2.join();
    t3.join();

    // 记录结束时间
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // 输出总耗时
    std::cout << "All tasks completed in " << elapsed.count() << " seconds." << std::endl;

    return 0;
}