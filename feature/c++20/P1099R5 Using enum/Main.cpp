#include <iostream>

enum class Channel {
    RED,
    GREEN,
    BLUE,
    ALPHA
};

std::string getChannelName(Channel ch) {
    switch (ch) {
        using enum Channel;
        case RED:   return "RED";
        case GREEN: return "GREEN";
        case BLUE:  return "BLUE";
        case ALPHA: return "ALPHA";
        default:    throw std::exception("No such channel");
    }
}

void print(Channel ch) {
    std::cout << getChannelName(ch) << std::endl;
}

int main() try
{
    print(Channel::RED);
    print(Channel::GREEN);
    print(Channel::BLUE);
    print(Channel::ALPHA);
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}
