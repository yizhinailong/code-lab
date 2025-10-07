#pragma once

#include <print>

#ifdef NDEBUG
    #define dbg(x)
#else
    #define dbg(x) ([&](auto&& v) { \
        return dbg_base(std::forward<decltype(v)>(v), #x, __FILE__, __LINE__); \
    }(x))
#endif

inline auto dbg_base(auto&& v, std::string_view expr, const char* file, int line) {
    std::println("[{}:{}] {} = {}", file, line, expr, v);
    if constexpr (std::is_lvalue_reference_v<decltype(v)>) {
        return (v);
    } else {
        return std::forward<decltype(v)>(v);
    }
};
