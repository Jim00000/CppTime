#include <iostream>
#include <algorithm>
#include <span>
#include <array>

int main()
{
    std::array numberSequece = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    auto it = numberSequece.cbegin();
    std::advance(it, 10);
    std::span visitor { it, numberSequece.cend() };
    std::cout << visitor.front() << std::endl;          // 10
    std::cout << visitor.subspan(5)[1] << std::endl;    // 16
    return 0;
}