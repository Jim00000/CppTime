#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <type_traits>
#include <vector>

template <typename Fn, typename... Args>
concept Callable = requires (Fn func, Args... args) {
    std::is_function_v<Fn>;
    func(args...);
};

auto buildData() noexcept
{
    return std::vector<uint16_t> {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
    };
}

template<typename T>
requires std::is_integral_v<T>
constexpr bool isEven(const T value) noexcept
{
    return (value & static_cast<T>(0x1)) == static_cast<T>(0);
}

template<typename T>
requires std::is_integral_v<T>
constexpr bool isOdd(const T value) noexcept
{
    return not isEven(value);
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_001_before(const std::vector<T>& data, Fn print) noexcept
{
    std::for_each(data.cbegin(), data.cend(), print);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_001_after(const std::vector<T>& data, Fn print) noexcept
{
    std::ranges::for_each(std::as_const(data), print);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_002_before(const std::vector<T>& data, Fn print) noexcept
{
    std::for_each(data.crbegin(), data.crend(), print);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_002_after(const std::vector<T>& data, Fn print) noexcept
{
    for (const auto datum : data | std::views::reverse)
        print(datum);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_003_before(const std::vector<T>& data, Fn print) noexcept
{
    std::for_each(data.crbegin(), data.crend(), print);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_003_after(const std::vector<T>& data, Fn print) noexcept
{
    for (const auto datum : data | std::views::reverse | std::views::filter(isEven<T>))
        print(datum);
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_004_before(std::vector<T>& data, Fn print) noexcept
{
    for (size_t i = 2; i < 5; i++)
        print(data.at(i));
    std::cout << std::endl;
}

template<typename T, typename Fn>
requires std::is_integral_v<T>&& Callable<Fn, T>
void example_004_after(const std::vector<T>& data, Fn print) noexcept
{
    for (const auto datum : data | std::views::drop(2) | std::views::take(3))
        print(datum);
    std::cout << std::endl;
}

int main(void) try
{
    auto data = buildData();

    auto print = [](const auto datum) {
        std::cout << datum << " ";
    };

    example_001_before(data, print);
    example_001_after(data, print);

    std::cout << std::endl;

    example_002_before(data, print);
    example_002_after(data, print);

    std::cout << std::endl;

    example_003_before(data, [](const auto datum) {
        if(datum % 2 == 0)
        std::cout << datum << " ";
    });
    example_003_after(data, print);

    std::cout << std::endl;

    example_004_before(data, print);
    example_004_after(data, print);

    std::cout << std::endl;

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Reference  & Credits :
// - Marius Bancila's Blog (C++ code samples before and after Ranges)
// https://mariusbancila.ro/blog/2019/01/20/cpp-code-samples-before-and-after-ranges/
// Most examples comes from here.
////////////////////////////////////////////////////////////////////////////////////////////////////