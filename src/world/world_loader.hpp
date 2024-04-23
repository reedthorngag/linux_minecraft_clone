#include <pthread.h>

#include "../util/world_gen_queue.hpp"

#ifndef _WORLD_LOADER
#define _WORLD_LOADER

const int NUM_THREADS = 1;

class WorldLoader {

    private:
        bool die = false;
        pthread_t thread_pool[NUM_THREADS] { 0 };
        

        static void* thread(void* data);

    public:
        WorldGenQueue queue;
        void pushChunk(Chunk* chunk);
        WorldLoader();
        ~WorldLoader();
};

#endif
