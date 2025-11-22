#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

int main() {

    spdlog::init_thread_pool(8192, 1);

    auto async_file_logger = spdlog::basic_logger_mt<spdlog::async_factory>("async_logger", "logs/async_log.log");
    spdlog::set_default_logger(async_file_logger);
    spdlog::info("This is an async log message");

    return 0;
}
