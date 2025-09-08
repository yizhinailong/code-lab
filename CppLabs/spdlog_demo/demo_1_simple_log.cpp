#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Hello, {}!", "world");
    spdlog::error("An error occurred: {}", "file not found");
    spdlog::warn("This is a warning with number: {}", 42);
    spdlog::critical("Support for int: {0:d}; hex: {0:x}; oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    return 0;
}
