#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>


struct Worker {
    uint64_t ID;
    std::wstring name;
    uint32_t salary;
};

struct Defender {
    uint16_t hitPoints;
    uint16_t attackPoints;
};

struct SecurityGuard : Worker, Defender {};

template <typename T>
requires (std::is_base_of_v<Worker, T>)
constexpr T build(
    const decltype(Worker::ID) id, 
    const decltype(Worker::name) name, 
    const decltype(Worker::salary) salary,
    std::function<void(T&)> initializer = nullptr
) noexcept
{
    T worker;               // default initialization
    worker.ID = id;
    worker.name = name;
    worker.salary = salary;
    if (initializer != nullptr) {
        initializer(worker);
    }
    return worker;
}

int main(void) try
{
    struct SecurityGuard securityGuard = build<struct SecurityGuard>(0ui64, L"SomeBody", 1000ui32, [=](struct SecurityGuard& guard) {
        guard.hitPoints = 1000ui16;
        guard.attackPoints = 200ui32;
    });
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}