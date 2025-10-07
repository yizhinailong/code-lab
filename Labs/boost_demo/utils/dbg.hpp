#pragma once

#include <print>

#ifdef DEBUG_MODE
    #define dbg(x) ([&](auto&& v) { \
        std::println("[{}:{}] {} = {}", __FILE__, __LINE__, #x, v); \
        if constexpr (std::is_lvalue_reference_v<decltype(x)>) { \
            return (v); \
        } else { \
            return std::forward<decltype(v)>(v); \
        } \
    }(x))

#else
    #define dbg(x)
#endif
