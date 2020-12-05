#include <iostream>
#include <thread>
#include <mutex>
#include <barrier>

void print_something(size_t start, size_t end) noexcept {
    static std::mutex mtx;
    const std::lock_guard<std::mutex> lock(mtx);
    for (auto i = start; i < end; i++) {
        std::cout << i << std::endl;
    }
}

void sync_print_something(std::barrier<>& barrier, size_t start, size_t end) noexcept {
    barrier.arrive_and_wait();
    print_something(start, end);
}

int main() try
{
    std::barrier barrier{ 2 };
    std::thread t1{ sync_print_something, std::ref(barrier), 0, 10};
    std::thread t2{ sync_print_something, std::ref(barrier), 100, 110 };
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}