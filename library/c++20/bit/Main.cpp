#include <bit>
#include <bitset>
#include <iostream>

int main(void) try
{
    switch (std::endian::native) {
    case std::endian::big:
        std::cout << "endian: big endian" << std::endl;
        break;
    case std::endian::little:
        std::cout << "endian: little endian" << std::endl;
        break;
    default:
        throw std::exception("unknown endian type");
        break;
    }

    constexpr std::uint8_t bit = 0b0000'0001;
    std::cout << "bit = " << std::bitset<8>(bit) << std::endl;
    std::cout << "rotl(bit, 1) = " << std::bitset<8>(std::rotl(bit, 1)) << std::endl;
    std::cout << "rotl(bit, 1) = " << std::bitset<8>(std::rotl(bit, 3)) << std::endl;
    std::cout << "popcount(00001001) = " << std::popcount(0b0000'1001ui64) << std::endl;
    std::cout << "popcount(01011101) = " << std::popcount(0b0101'1101ui64) << std::endl;
    std::cout << "has_single_bit(00000000) = " << std::boolalpha << std::has_single_bit(0b0000'0000ui64) << std::endl;
    std::cout << "has_single_bit(00000000) = " << std::boolalpha << std::has_single_bit(0b0000'1000ui64) << std::endl;
    std::cout << "bit_ceil(00000111) = " << std::bitset<8>(std::bit_ceil(0b0000'0111ui64)) << std::endl;

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}