#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include <cstddef>

int main() {
    auto rotating_logger = spdlog::rotating_logger_mt("rotating_logger",
                                                      "logs/rotating_log.log",
                                                      static_cast<size_t>(1024 * 1024 * 5),
                                                      3);
    // 日志文件最大5MB，最多保留3个文件
    spdlog::set_default_logger(rotating_logger);
    for (int i = 0; i < 10000; ++i) {
        spdlog::info("This is a rotating log message {}", i);
    }
    return 0;
}
