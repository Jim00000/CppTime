#include <iostream>

template<typename T>
struct Widget {
    T value;
    void f(T new_value) {
        [=, this] {
            this->value = new_value;
        }();
    }
};

int main() try
{
    struct Widget<int> widget {.value = 1};
    widget.f(2);
    std::cout << widget.value << std::endl;
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}