#include <iostream>

void foo(const int argc)
{
    if (argc == 0) [[unlikely]] {
        std::cout << "There are no arguments" << std::endl;
    }
    else if (argc == 1) [[likely]] {
        std::cout << "There is one argument" << std::endl;
    }
    else [[unlikely]] {
        std::cout << "There are more than one arguments" << std::endl;
    }
}

int main(const int argc, const char* const argv[]) try
{
    foo(argc);
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}