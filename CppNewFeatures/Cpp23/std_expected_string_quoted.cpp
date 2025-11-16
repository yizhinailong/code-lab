#include <cmath>
#include <cstdint>
#include <expected>
#include <iomanip>
#include <iostream>
#include <string_view>

enum class parse_error : std::int8_t {
    invalid_input,
    overflow
};

static auto parse_number(std::string_view& str) -> std::expected<double, parse_error> {
    const char* begin = str.data();
    char* end = nullptr;
    double retval = std::strtod(begin, &end);

    if (begin == end) {
        return std::unexpected(parse_error::invalid_input);
    }

    if (std::isinf(retval)) {
        return std::unexpected(parse_error::overflow);
    }

    str.remove_prefix(end - begin);
    return retval;
}

int main() {
    auto process = [](std::string_view str) {
        std::cout << "str: " << std::quoted(str) << ", ";
        if (const auto num = parse_number(str); num.has_value()) {
            std::cout << "value: " << *num << '\n';
        } else if (num.error() == parse_error::invalid_input) {
            std::cout << "error: invalid input\n";
        } else if (num.error() == parse_error::overflow) {
            std::cout << "error: overflow\n";
        } else {
            std::cout << "unexpected!\n";
        }
    };

    for (const auto* src : { "42", "42abc", "meow", "inf" }) {
        process(src);
    }

    return 0;
}
