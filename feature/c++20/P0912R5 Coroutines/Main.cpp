#include <iostream>
#include <coroutine>

template<typename T>
struct resumable {
    struct promise_type {

        T value;

        resumable get_return_object() {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        auto initial_suspend() { return std::suspend_always(); }

        auto final_suspend()  { return std::suspend_always(); }

        void return_void() {}

        // void return_value(int value) { this->value = value; }

        auto yield_value(T value) {
            this->value = value;
            return std::suspend_always();
        }

        void unhandled_exception() {
            std::terminate();
        }
    };

    resumable(std::coroutine_handle<promise_type> handle) : handle(handle) {}

    ~resumable() { handle.destroy(); }

    resumable(resumable&) = delete;

    resumable(resumable&&) = delete;

    const bool resume() const {
        if (not handle.done())
            handle.resume();
        return not handle.done();
    }

    const T get() const {
        return handle.promise().value;
    }

    std::coroutine_handle<promise_type> handle;
};

template<typename T>
T cumulative_sum_consumer(resumable<T>& producer) {
    T sum = 0;
    while (producer.resume())
        sum += producer.get();
    return sum;
}   

template<typename T>
resumable<T> cumulative_sum_producer(T start, T end, T step) noexcept {
    for (T value = start; value <= end; value += step) {
        co_yield value;
    }
}

template<typename T>
T cumulative_sum(T start, T end, T step) {
    resumable producer = cumulative_sum_producer(start, end, step);
    return cumulative_sum_consumer(producer);
}

int main() {
    std::cout << cumulative_sum(0, 5, 1) << std::endl;          // output : 15
    std::cout << cumulative_sum(0.0, 5.6, 2.1) << std::endl;    // output : 6.3
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Resources & References
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - YOUR FIRST COROUTINE -
// https://blog.panicsoftware.com/your-first-coroutine/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////