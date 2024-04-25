#include <pthread.h>

#include "../util/synchronized_queue.hpp"

#ifndef _WORLD_LOADER
#define _WORLD_LOADER

const int NUM_THREADS = 8;

struct Chunk;

class WorldLoader {

    private:
        bool die = false;
        pthread_t thread_pool[NUM_THREADS] { 0 };
        
        static void* thread(void* data);

    public:
        SynchronizedQueue<Chunk*> meshingQueue;
        SynchronizedQueue<Chunk*> genBufferQueue;
        void pushChunk(Chunk* chunk);
        WorldLoader();
        ~WorldLoader();
};

#endif
