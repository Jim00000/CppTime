#include <iostream>
#include <thread>
#include <atomic>
#include <barrier>
#include <mutex>

void outputThreadReadyMessage(size_t idx) noexcept
{
    static std::mutex _mutex;
    std::scoped_lock lock{ _mutex };
    std::cout << "thread " << idx << " is ready." << std::endl;
}

template<typename T, size_t COUNTS = 1000000>
void increment(size_t idx, std::barrier<>& barrier, T& counter) noexcept
{
    outputThreadReadyMessage(idx);
    barrier.arrive_and_wait();
    for (size_t i = 0; i < COUNTS; i++)
        counter++;
}

int main() try
{
    using counter_t = uint32_t;
    counter_t counter = 0;
    std::barrier barrier{ 2 };
    std::thread t1{ increment<decltype(counter)>, 1, std::ref(barrier), std::ref(counter) };
    std::thread t2{ increment<decltype(counter)>, 2, std::ref(barrier), std::ref(counter) };
    t1.join();
    t2.join();
    std::cout << counter << std::endl << std::endl;

    
    std::atomic<counter_t> atomic_counter = 0;
    std::thread t3{ increment<decltype(atomic_counter)>, 3, std::ref(barrier), std::ref(atomic_counter) };
    std::thread t4{ increment<decltype(atomic_counter)>, 4, std::ref(barrier), std::ref(atomic_counter) };
    t3.join();
    t4.join();
    std::cout << atomic_counter << std::endl;
   

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}