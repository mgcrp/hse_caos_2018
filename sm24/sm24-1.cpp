#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

double values[3];
std::mutex local_mutex;
const int THREAD_NUMBER = 3;
const int ITER_NUMBER = 1000000;

void thread_func(int add_to, int add_value, int substract_from, int substract_value) {
    for (int i = 0; i < ITER_NUMBER; ++i) {
        std::lock_guard<std::mutex> lock(local_mutex);
        values[add_to] += add_value;
        values[substract_from] -= substract_value;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        threads.emplace_back(thread_func, i, 80 + (20 * i), (i + 1) % THREAD_NUMBER, 90 + 20 * i);
    }
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        threads[i].join();
    }
    std::cout << values[0] << " " << values[1] << " " << values[2] << "\n";
    return 0;
}
