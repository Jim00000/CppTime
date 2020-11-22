module;

#include <type_traits>
#include <concepts>

export module arithmatic;

template<typename T>
concept Addable = requires (T x) { x + x; };

namespace Arithmatic {

    template <typename T>
    T add(T first) { // private
        return first;
    }

    export
        template<typename T, typename... Ts> requires Addable<T>&& requires(T first, Ts... args) {
        std::is_same_v<T, std::common_type_t<Ts...>>;
    }
    T add(T first, Ts... args) { // public
        return first + add(args...);
    }

}