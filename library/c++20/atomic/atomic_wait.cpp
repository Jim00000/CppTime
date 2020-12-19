#include <array>
#include <atomic>
#include <iostream>
#include <thread>

struct Buffer {
    Buffer() : msg{}, condition{ false } {}
    std::array<char, 256> msg;
    std::atomic<volatile bool> condition;
};

void dataBuilder(struct Buffer& buffer)
{
    std::array<char, 256> message { "Hello World" };
    std::cout << "Start dataBuilder thread" << std::endl;
    memcpy(buffer.msg.data(), message.data(), message.max_size());
    std::cout << "End dataBuilder thread" << std::endl;
    buffer.condition.store(true);
    buffer.condition.notify_one();
}

void printData(struct Buffer& buffer)
{
    buffer.condition.wait(false , std::memory_order::relaxed);
    std::cout << "Start printData thread" << std::endl;
    std::cout << "buffer.msg = " << buffer.msg.data() << std::endl;
    std::cout << "End printData thread" << std::endl;
}

int main(void) try
{
    struct Buffer buffer;
    std::thread producer{ dataBuilder, std::ref(buffer) };
    std::thread consumer{ printData, std::ref(buffer) };
    producer.join();
    consumer.join();

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}