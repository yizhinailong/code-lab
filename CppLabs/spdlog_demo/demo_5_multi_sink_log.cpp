#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.log");

    spdlog::logger multi_sink_logger("multi_sink", { console_sink, file_sink });
    multi_sink_logger.set_level(spdlog::level::debug);
    multi_sink_logger.warn("This message goes to both console and file");

    return 0;
}
