#include <iostream>
#include <variant>

static void std_variant_get() {
    std::variant<int, double> var_1{ 10 };

    auto var_2 = std::get<int>(var_1);
    std::cout << "std::get<int>(var_1): " << var_2 << std::endl;

    var_2 = std::get<0>(var_1);
    std::cout << "std::get<0>(var_1): " << var_2 << std::endl;

    try {
        auto var_3 = std::get<double>(var_1);
        std::cout << "std::get<double>(var_1): " << var_3 << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

static void std_variant_get_if() {
    std::variant<int, double> var_1{ 10 };

    if (auto* pval = std::get_if<int>(&var_1)) {
        std::cout << "std::get_if<int>(&var_1): " << *pval << std::endl;
    } else {
        std::cout << "Failed to get int value!" << std::endl;
    }

    if (auto* pval = std::get_if<double>(&var_1)) {
        std::cout << "std::get_if<double>(&var_1): " << *pval << std::endl;
    } else {
        std::cout << "Failed to get double value!" << std::endl;
    }
}

static void std_variant_holds_alternative() {
    std::variant<int, double> var = 10;
    std::cout << std::boolalpha
              << "variant holds int? "
              << std::holds_alternative<int>(var) << '\n'
              << "variant holds double? "
              << std::holds_alternative<double>(var) << '\n';
}

int main() {
    std::cout << "std_variant_get: " << std::endl;
    std_variant_get();
    std::cout << std::endl;

    std::cout << "std_variant_get_if: " << std::endl;
    std_variant_get_if();
    std::cout << std::endl;

    std::cout << "std_variant_holds_alternative: " << std::endl;
    std_variant_holds_alternative();
    std::cout << std::endl;

    return 0;
}
