#include <iostream>

import arithmatic;

int main() {
    //std::cout << add(1) << std::endl;                     // Compilation error. No such function
    std::cout << Arithmatic::add(1, 2, 3) << std::endl;     // output: 6
    return 0;
}
