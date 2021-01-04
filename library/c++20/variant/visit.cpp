#include <iomanip>
#include <iostream>
#include <string>
#include <variant>
#include <vector>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

int main(void) try
{
    using var_t = std::variant<int, float, std::string>;
    std::vector<var_t> vec;
    vec.push_back(1);
    vec.push_back(2.0f);
    vec.push_back("3");

    for (auto& v : vec) {
        std::visit(overloaded{
            [](auto arg) {std::cout << arg << ' '; },
            [](float arg) { std::cout << std::fixed << arg << ' '; },
            [](const std::string& arg) { std::cout << "\"" << arg << "\"" << ' '; },
        }, v);
    }

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}