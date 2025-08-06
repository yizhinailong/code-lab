#include <iostream>
#include <string>
#include <variant>
#include <vector>

static void std_variant_visit_if_constexpr() {
    std::variant<int, double> var_1{ 10 };
    std::variant<int, double> var_2{ 20.5 };

    auto visitor = [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Visiting int: " << arg << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "Visiting double: " << arg << std::endl;
        }
    };

    std::visit(visitor, var_1);
    std::visit(visitor, var_2);
}

template <typename... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

static void std_variant_visit_overloaded() {
    std::vector<std::variant<int, double, std::string>> vars{ 1, 2.5, 3, 4.0, "Hello", "World" };

    auto visitor = overloaded{
        [](int i) {
            std::cout << "Visiting int: " << i << std::endl;
        },
        [](double d) {
            std::cout << "Visiting double: " << d << std::endl;
        },
        [](const std::string& s) {
            std::cout << "Visiting string: " << s << std::endl;
        }
    };

    for (auto& var : vars) {
        std::visit(visitor, var);
    }
}

int main() {

    std::cout << "std_variant_visit_if_constexpr: " << std::endl;
    std_variant_visit_if_constexpr();
    std::cout << std::endl;

    std::cout << "std_variant_visit_overloaded: " << std::endl;
    std_variant_visit_overloaded();
    std::cout << std::endl;

    return 0;
}
