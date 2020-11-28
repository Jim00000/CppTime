#include <iostream>

int main() try
{
    struct Widget { int a; float b; char c; };
    struct Widget w1 { .a = 1 };
    struct Widget w2 { .b = 1.0f };
    struct Widget w3 { .b = 1.0f, .c = 'c' };

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}