#include <pthread.h>

#ifndef _WORLD_LOADER
#define _WORLD_LOADER

const int NUM_THREADS = 6;

class WorldLoader {

    private:
        pthread_t thread_pool[NUM_THREADS] { 0 };

        static void* thread(void* data);

    public:
        WorldLoader();
        ~WorldLoader();
};

#endif
