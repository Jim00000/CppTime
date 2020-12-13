#include <array>
#include <iostream>

auto initializer() {
    return std::array{
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
}

int main(void) try
{
    for (const auto container = initializer(); auto & data : container) {
        std::cout << data << std::endl;
    }

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}