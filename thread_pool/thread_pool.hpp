#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

class ThreadPool {
public:
    explicit ThreadPool(size_t threads);

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    template <typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>>;

    ~ThreadPool();

private:
    // need to keep track of threads so we can join them
    std::vector<std::thread> _workers;
    // the task queue
    std::queue<std::function<void()>> _tasks;

    // synchronization
    std::mutex _queue_mutex;
    std::condition_variable _condition;
    bool _stop{ false };
};

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads) {
    for (size_t i = 0; i < threads; ++i) {
        _workers.emplace_back(
            [this]() {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(this->_queue_mutex);
                        this->_condition.wait(
                            lock,
                            [this]() -> bool {
                                return this->_stop || !this->_tasks.empty();
                            });
                        if (this->_stop && this->_tasks.empty()) {
                            return;
                        }
                        task = std::move(this->_tasks.front());
                        this->_tasks.pop();
                    }

                    task();
                }
            });
    }
}

// add new work item to the pool
template <typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
    using return_type = std::invoke_result_t<F, Args...>;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        [f = std::forward<F>(f), args...]() -> return_type {
            return std::invoke(f, args...);
        });

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (_stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }

        _tasks.emplace([task]() { (*task)(); });
    }
    _condition.notify_one();
    return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_queue_mutex);
        _stop = true;
    }
    _condition.notify_all();
    for (std::thread& worker : _workers) {
        worker.join();
    }
}
