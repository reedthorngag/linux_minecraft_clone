#include <mutex>
#include <queue>
#include <condition_variable>

#include "../world/chunk.hpp"

#ifndef WORLD_GEN_QUEUE
#define WORL_GEN_QUEUE

template <typename T>
class SynchronizedQueue {
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable condition;

    public:
        void push(T chunk) {
            std::unique_lock<std::mutex> lock(this->mutex);

            this->queue.push(item);

            this->condition.notify_one();
        }
        T pop() {
            std::unique_lock<std::mutex> lock(this->mutex);
            
            condition.wait(lock,[this]() { return !queue.empty(); });

            T item = queue.front();
            queue.pop();

            return T;
        }
};

#endif
