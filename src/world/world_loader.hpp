#include <pthread.h>

#include "../util/synchronized_queue.hpp"
#include "./generation/world_gen.hpp"

#ifndef _WORLD_LOADER
#define _WORLD_LOADER

const int NUM_MESHING_THREADS = 6;
const int NUM_GEN_THREADS = 6;

struct Chunk;
struct World;

class WorldLoader {

    private:
        bool die = false;
        pthread_t mesh_thread_pool[NUM_MESHING_THREADS] { 0 };
        pthread_t gen_thread_pool[NUM_MESHING_THREADS] { 0 };

        SynchronizedQueue<Chunk*> genQueue;
        SynchronizedQueue<Chunk*> meshingQueue;

        World* world;
        
        
        static void* meshingThread(void* data);
        static void* genThread(void* data);

    public:
        WorldGenerator worldGen;
        SynchronizedQueue<Chunk*> genBufferQueue;

        void genChunk(int pos[2]);
        void meshChunk(Chunk* chunk);
        WorldLoader(World* world);
        ~WorldLoader();
};

#endif
