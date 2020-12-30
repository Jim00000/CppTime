#include <iostream>
#include <numbers>

int main(void) try
{
    std::cout << "value of e : " << std::numbers::e << std::endl;
    std::cout << "value of log2e : " << std::numbers::log2e << std::endl;
    std::cout << "value of pi : " << std::numbers::pi << std::endl;
    std::cout << "value of ln2 : " << std::numbers::ln2 << std::endl;
    std::cout << "value of sqrt2 : " << std::numbers::sqrt2 << std::endl;

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}