#include <iostream>
#include <mutex>
#include <latch>

void initializeSomething(size_t tid) noexcept
{
    static std::once_flag flag;
    static std::latch arriving_point{ 4 };
    arriving_point.arrive_and_wait();
    std::call_once(flag, [=] {std::cout << "Thread id " << tid << " initializes this function first." << std::endl; });
}

int main() try
{
    std::thread t1 { std::ref(initializeSomething), 1 };
    std::thread t2 { std::ref(initializeSomething), 2 };
    std::thread t3 { std::ref(initializeSomething), 3 };
    std::thread t4 { std::ref(initializeSomething), 4 };

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}