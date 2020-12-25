#include <iostream>
#include <type_traits>
#include <vector>

int main(void) try
{
    std::vector<float> values;

    auto f = [=]<typename T>(std::vector<T>) {
        if constexpr (std::is_same_v<T, int>)
            std::cout << "T = int" << std::endl;
        else if constexpr (std::is_same_v<T, float>)
            std::cout << "T = float" << std::endl;
        else
            static_assert(std::false_type::value, "uncategorized types");
        std::cout << "sizeof(T) is " << sizeof(T) << std::endl;
    };

    f(values);

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}