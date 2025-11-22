#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <random>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <vector>

// 日志级别枚举
enum class LogLevel : std::uint8_t {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

// 日志记录器类
class Logger {
private:
    std::mutex log_mutex;
    LogLevel current_level = LogLevel::INFO;

public:
    void set_level(LogLevel level) { current_level = level; }

    void log(LogLevel level, const std::string& message) {
        if (level >= current_level) {
            std::lock_guard<std::mutex> lock(log_mutex);
            std::cout << "[" << level_to_string(level) << "] " << message << '\n';
        }
    }

    // 支持格式化字符串的日志方法（兼容C++11/14/17）
    template <typename... Args>
    void debug(const std::string& format, const Args&... args) {
        log(LogLevel::DEBUG, format_string(format, args...));
    }

    template <typename... Args>
    void info(const std::string& format, const Args&... args) {
        log(LogLevel::INFO, format_string(format, args...));
    }

    template <typename... Args>
    void warning(const std::string& format, const Args&... args) {
        log(LogLevel::WARNING, format_string(format, args...));
    }

    template <typename... Args>
    void error(const std::string& format, const Args&... args) {
        log(LogLevel::ERROR, format_string(format, args...));
    }

private:
    // 辅助函数：格式化字符串
    template <typename... Args>
    auto format_string(const std::string& format, const Args&... args)
        -> std::string {
        std::ostringstream oss;
        format_helper(oss, format, args...);
        return oss.str();
    }

    // 递归辅助函数
    template <typename T, typename... Args>
    static void format_helper(std::ostringstream& oss,
                              const std::string& format,
                              const T& value,
                              const Args&... args) {
        size_t pos = format.find("{}");
        if (pos != std::string::npos) {
            oss << format.substr(0, pos) << value;
            // 检查是否还有足够的参数来匹配剩余的占位符
            if constexpr (sizeof...(args) > 0) {
                format_helper(oss, format.substr(pos + 2), args...);
            } else {
                // 没有更多参数了，直接输出剩余格式字符串
                oss << format.substr(pos + 2);
            }
        } else {
            oss << format;
        }
    }

    // 递归终止函数
    static void format_helper(std::ostringstream& oss, const std::string& format) {
        oss << format;
    }

    static auto level_to_string(LogLevel level) -> std::string {
        switch (level) {
            case LogLevel::DEBUG  : return "DEBUG";
            case LogLevel::INFO   : return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR  : return "ERROR";
            default               : return "UNKNOWN";
        }
    }
};

// 统计信息类
class DiningStats {
private:
    std::mutex stats_mutex;
    std::vector<int> meals_eaten;
    std::vector<std::chrono::milliseconds> total_eating_time;
    std::vector<std::chrono::milliseconds> total_thinking_time;

public:
    explicit DiningStats(int num_philosophers)
        : meals_eaten(num_philosophers, 0),
          total_eating_time(num_philosophers, std::chrono::milliseconds(0)),
          total_thinking_time(num_philosophers, std::chrono::milliseconds(0)) {}

    void add_meal(int philosopher_id, std::chrono::milliseconds eating_time) {
        std::lock_guard<std::mutex> lock(stats_mutex);
        meals_eaten[philosopher_id]++;
        total_eating_time[philosopher_id] += eating_time;
    }

    void add_thinking_time(int philosopher_id, std::chrono::milliseconds thinking_time) {
        std::lock_guard<std::mutex> lock(stats_mutex);
        total_thinking_time[philosopher_id] += thinking_time;
    }

    void print_stats() {
        std::lock_guard<std::mutex> lock(stats_mutex);
        std::cout << "\n=== Dining Statistics ===\n";
        for (int i = 0; i < meals_eaten.size(); ++i) {
            std::cout << "Philosopher " << i << ": "
                      << meals_eaten[i] << " meals, "
                      << "eating: " << total_eating_time[i].count() << "ms, "
                      << "thinking: " << total_thinking_time[i].count() << "ms\n";
        }
        std::cout << "========================\n";
    }
};

// 配置结构体
struct DiningConfig {
    int num_philosophers = 5;
    int num_meals = 3;
    int min_think_eat_time = 1;
    int max_think_eat_time = 3;
    LogLevel log_level = LogLevel::INFO;
    bool enable_stats = true;

    static auto from_args(int argc, char* argv[]) -> DiningConfig {
        DiningConfig config;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--philosophers" && i + 1 < argc) {
                config.num_philosophers = std::stoi(argv[++i]);
            } else if (arg == "--meals" && i + 1 < argc) {
                config.num_meals = std::stoi(argv[++i]);
            } else if (arg == "--min-time" && i + 1 < argc) {
                config.min_think_eat_time = std::stoi(argv[++i]);
            } else if (arg == "--max-time" && i + 1 < argc) {
                config.max_think_eat_time = std::stoi(argv[++i]);
            } else if (arg == "--log-level") {
                if (i + 1 < argc) {
                    std::string level = argv[++i];
                    if (level == "debug") {
                        config.log_level = LogLevel::DEBUG;
                    } else if (level == "info") {
                        config.log_level = LogLevel::INFO;
                    } else if (level == "warning") {
                        config.log_level = LogLevel::WARNING;
                    } else if (level == "error") {
                        config.log_level = LogLevel::ERROR;
                    }
                }
            } else if (arg == "--no-stats") {
                config.enable_stats = false;
            } else if (arg == "--help") {
                print_help();
                exit(0);
            }
        }

        // 验证配置
        if (config.num_philosophers <= 0) {
            throw std::invalid_argument("Number of philosophers must be positive");
        }
        if (config.num_meals <= 0) {
            throw std::invalid_argument("Number of meals must be positive");
        }
        if (config.min_think_eat_time <= 0 || config.max_think_eat_time <= 0) {
            throw std::invalid_argument("Think/eat time must be positive");
        }
        if (config.min_think_eat_time > config.max_think_eat_time) {
            throw std::invalid_argument("Min time cannot be greater than max time");
        }

        return config;
    }

private:
    static void print_help() {
        std::cout << "Usage: ./dining_philosophers [options]\n"
                  << "Options:\n"
                  << "  --philosophers N     Number of philosophers (default: 5)\n"
                  << "  --meals N           Number of meals per philosopher (default: 3)\n"
                  << "  --min-time N        Minimum think/eat time in seconds (default: 1)\n"
                  << "  --max-time N        Maximum think/eat time in seconds (default: 3)\n"
                  << "  --log-level LEVEL   Log level (debug|info|warning|error) (default: info)\n"
                  << "  --no-stats          Disable statistics collection\n"
                  << "  --help              Show this help message\n";
    }
};

// 哲学家类
class Philosopher {
private:
    int id;
    int left_fork;
    int right_fork;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    Logger& logger;
    DiningStats& stats;
    const DiningConfig& config;

public:
    Philosopher(int id,
                int num_philosophers,
                Logger& logger,
                DiningStats& stats,
                const DiningConfig& config)
        : id(id),
          left_fork(id),
          right_fork((id + 1) % num_philosophers),
          gen(std::random_device{}()),
          dis(config.min_think_eat_time, config.max_think_eat_time),
          logger(logger),
          stats(stats),
          config(config) {}

    void dine(std::vector<std::mutex>& forks) {
        logger.debug("Philosopher " + std::to_string(id) + " starting dining session");

        for (int meal = 0; meal < config.num_meals; ++meal) {
            try {
                // 思考阶段
                auto think_start = std::chrono::steady_clock::now();
                logger.info("Philosopher {} is thinking...", id);
                std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
                auto think_end = std::chrono::steady_clock::now();
                stats.add_thinking_time(id, std::chrono::duration_cast<std::chrono::milliseconds>(think_end - think_start));

                // 获取叉子 - 使用std::scoped_lock确保原子性
                logger.debug("Philosopher {} attempting to acquire forks", id);
                std::scoped_lock lock(forks[left_fork], forks[right_fork]);
                logger.info("Philosopher {} picked up both forks", id);

                // 用餐阶段
                auto eat_start = std::chrono::steady_clock::now();
                logger.info("Philosopher {} is eating meal {}...", id, meal + 1);
                std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));
                auto eat_end = std::chrono::steady_clock::now();
                stats.add_meal(id, std::chrono::duration_cast<std::chrono::milliseconds>(eat_end - eat_start));

                logger.info("Philosopher {} finished eating and put down forks", id);

            } catch (const std::exception& e) {
                logger.error("Philosopher {} encountered error: {}", id, e.what());
                throw; // 重新抛出异常，让上层处理
            }
        }

        logger.info("Philosopher {} has finished all meals", id);
    }
};

// 餐厅管理类
class DiningPhilosophers {
private:
    std::vector<std::mutex> forks;
    Logger logger;
    DiningStats stats;
    const DiningConfig config;

public:
    explicit DiningPhilosophers(const DiningConfig& config)
        : config(config),
          stats(config.num_philosophers),
          forks(config.num_philosophers) {

        logger.set_level(config.log_level);
        logger.info("Initializing dining simulation with {} philosophers", config.num_philosophers);
    }

    void run() {
        std::vector<std::thread> philosophers;
        philosophers.reserve(config.num_philosophers);

        logger.info("Starting dining simulation...");

        // 创建哲学家线程
        for (int i = 0; i < config.num_philosophers; ++i) {
            philosophers.emplace_back([this, i]() {
                Philosopher philosopher(i, config.num_philosophers, logger, stats, config);
                philosopher.dine(forks);
            });
        }

        // 等待所有哲学家线程完成
        for (auto& p : philosophers) {
            p.join();
        }

        logger.info("All philosophers have finished dining");

        if (config.enable_stats) {
            stats.print_stats();
        }
    }
};

// 主函数
auto main(int argc, char* argv[]) -> int {
    try {
        // 解析配置
        auto config = DiningConfig::from_args(argc, argv);

        // 创建并运行餐厅模拟
        DiningPhilosophers dining(config);
        dining.run();

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
