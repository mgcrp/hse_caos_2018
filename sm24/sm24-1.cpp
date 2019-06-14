#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

const int ITERATIONS = 1000000;
const int THREADS_NUM = 3;

double arr[3];
std::mutex m;

void thread_func(int add_idx, int add_val, int sub_idx, int sub_val) {
    for (int i = 0; i < ITERATIONS; ++i) {
        std::lock_guard<std::mutex> lock(m);
        arr[add_idx] += add_val;
        arr[sub_idx] -= sub_val;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < THREADS_NUM; ++i) {
        threads.emplace_back(thread_func, i, 80 + (20 * i), (i + 1) % THREADS_NUM, 90 + 20 * i);
    }
    for (int i = 0; i < THREADS_NUM; ++i) {
        threads[i].join();
    }
    std::cout << arr[0] << " " << arr[1] << " " << arr[2] << "\n";
    return 0;
}
