#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

int main() {
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic.log");
    file_logger->info("This message goes to the file");
    file_logger->error("This is an error message in the file");
    file_logger->warn("This is a warning message in the file");
    file_logger->critical("Critical issue logged in the file");
    file_logger->debug("Debugging info in the file");
    file_logger->info("Formatted number: {:03.2f}", 1.23456);
    file_logger->info("Positional args are {1} {0}..", "second", "first");

    return 0;
}
