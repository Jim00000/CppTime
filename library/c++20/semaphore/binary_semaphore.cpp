#include <iostream>
#include <semaphore>
#include <thread>

std::binary_semaphore sem_main{ 0 }, sem_handler{0};

void handler()
{
    std::cout << "Handler starts" << std::endl;
    sem_handler.acquire();
    std::cout << "Handler ends" << std::endl;
    sem_main.release();
}

int main(void) try
{
    std::cout << "Main starts" << std::endl;

    std::thread event{ handler };

    sem_handler.release();

    sem_main.acquire();

    event.join();

    std::cout << "Main ends" << std::endl;
    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}