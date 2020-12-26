#include <atomic>
#include <barrier>
#include <future>
#include <iostream>
#include <memory>

template <typename T, size_t N>
constexpr size_t getArraySize(const T(&)[N]) {
    return N;
}

template <typename T>
class ConcurrentLinkList {
    struct Node {
        Node(const T data) {
            this->data = data;
        }
        T data;
        std::atomic<std::shared_ptr<struct Node>> next;
    };
public:
    static ConcurrentLinkList build(const T data = static_cast<T>(0)) {
        return ConcurrentLinkList{ data };
    }

    void push_front(const T data) noexcept {
        std::shared_ptr<struct Node> newHead = std::make_shared<struct Node>(data);
        newHead->next = this->head.load(std::memory_order_relaxed);
        {
            std::shared_ptr<struct Node> expected = newHead->next.load();
            while (not this->head.compare_exchange_weak(expected, newHead, std::memory_order_release)) {
                newHead->next = this->head.load(std::memory_order_relaxed);
                expected = newHead->next.load();
            }

            // head.store(newHead);
        }
    }

    void output() noexcept {
        std::weak_ptr<struct Node> visitor = head.load();
        while (visitor.lock() != nullptr && not visitor.expired()) {
            std::cout << visitor.lock()->data << " ";
            visitor = visitor.lock()->next.load();
        }
        std::cout << std::endl;
    }

    const size_t size() noexcept {
        size_t size = 0;
        std::weak_ptr<struct Node> visitor = head.load();
        while (visitor.lock() != nullptr && not visitor.expired()) {
            visitor = visitor.lock()->next.load();
            size++;
        }

        return size;
    }

private:
    ConcurrentLinkList() = delete;

    ConcurrentLinkList(const T data) : head(std::make_shared<struct Node>(data)) {}

    std::atomic<std::shared_ptr<struct Node>> head;
};

int main(void) try
{
    using datatype = int;
    ConcurrentLinkList linklist = ConcurrentLinkList<typename datatype>::build(-1);

    auto task = [&]<typename T>(const T data, const size_t count) -> void {
        static std::barrier<> fence{ 4 };
        fence.arrive_and_wait();
        for (auto i = 0; i < count; i++)
            linklist.push_front(data);
    };


    std::future<void> results[] = {
        std::async(std::launch::async, task, 1, 100),
        std::async(std::launch::async, task, 2, 100),
        std::async(std::launch::async, task, 3, 100),
        std::async(std::launch::async, task, 4, 100),
    };

    for (size_t i = 0; i < getArraySize(results); i++) {
        results[i].wait();
    }

    linklist.output();
    std::cout << linklist.size() << std::endl;

    return EXIT_SUCCESS;
}
catch (...) {
    std::cerr << "unidentified error catched" << std::endl;
    std::terminate();
}