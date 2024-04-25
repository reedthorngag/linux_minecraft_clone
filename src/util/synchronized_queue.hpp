#include <mutex>
#include <queue>
#include <condition_variable>

#ifndef _WORLD_GEN_QUEUE
#define _WORLD_GEN_QUEUE

template <typename T>
class SynchronizedQueue {
    public:
        std::queue<T> queue;
        std::condition_variable condition;
        std::mutex mutex;

        void push(T item) {
            std::unique_lock<std::mutex> lock(this->mutex);

            this->queue.push(item);

            this->condition.notify_one();
        }
        T pop() {
            std::unique_lock<std::mutex> lock(this->mutex);
            
            condition.wait(lock,[this]() { return !queue.empty(); });

            T item = queue.front();
            queue.pop();

            return item;
        }
};

#endif
