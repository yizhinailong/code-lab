#include <expected>
#include <print>

static auto Divide(int a, int b) -> std::expected<int, std::string> {
    if (b == 0) {
        return std::unexpected("Divide by 0 error!");
    }

    return a / b;
}

static void demo_expected() {
    auto result = Divide(12, 4)
                      .and_then([](int result) {
                          return Divide(result, 0);
                      })
                      .or_else([](const std::string& error) {
                          std::println("Error: {}", error);
                          return std::expected<int, std::string>{ 0 };
                      });
    if (result) {
        std::println("Result: {}", result.value());
    }
}

int main() {
    auto result = Divide(10, 2)
                      .and_then([](int result) {
                          std::println("Intermediate result: {}", result);
                          return Divide(result, 5);
                      })
                      .or_else([](const std::string& error) {
                          std::println("Error: {}", error);
                          return std::expected<int, std::string>{ 0 };
                      });

    if (result) {
        std::println("Result: {}", *result);
    }

    return 0;
}
