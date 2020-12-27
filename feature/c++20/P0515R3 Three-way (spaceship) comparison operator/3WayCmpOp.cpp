#include <iostream>
#include <utility>

template<typename T>
class Point {
public:
    Point(T x, T y) : x(x), y(y) {}

    const auto operator<=>(const Point&) const = default;

private:
    T x, y;
};

int main(void) try
{
    auto order = (1 <=> 1);
    std::cout << static_cast<int16_t>(order._Value) << std::endl;
    order = (1 <=> 0);
    std::cout << static_cast<int16_t>(order._Value) << std::endl;
    order = (0 <=> 1);
    std::cout << static_cast<int16_t>(order._Value) << std::endl;

    std::cout << static_cast<int16_t>((Point{ 1, 2 } <=> Point{ 1, 2 })._Value) << std::endl;
    std::cout << static_cast<int16_t>((Point{ 1, 2 } <=> Point{ 3, 4 })._Value) << std::endl;
    std::cout << static_cast<int16_t>((Point{ 2, 3 } <=> Point{ 1, 5 })._Value) << std::endl;
    std::cout << static_cast<int16_t>((Point{ 1, 3 } <=> Point{ 1, 5 })._Value) << std::endl;
    std::cout << static_cast<int16_t>((Point{ 1, 5 } <=> Point{ 1, 2 })._Value) << std::endl;

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}