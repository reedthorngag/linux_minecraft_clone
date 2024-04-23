#include <pthread.h>
#include <stdio.h>

#include "world_loader.hpp"

void* WorldLoader::thread(void* data) {
    WorldLoader* parent = (WorldLoader*)data;

    while (!parent->die) {
        Chunk* chunk = parent->queue.pop();
        printf("got chunk!\n");
        if (parent->die) return nullptr;
        chunk->gen_mesh();
        chunk->render();
    }

    return nullptr;
}

void WorldLoader::pushChunk(Chunk* chunk) {
    this->queue.push(chunk);
}


WorldLoader::WorldLoader() {
    for (pthread_t thread : thread_pool) {
        pthread_create(&thread,NULL,&WorldLoader::thread,this);
    }
}

WorldLoader::~WorldLoader() {
    this->die = true;
    for (int i=0;i<NUM_THREADS;i++) this->queue.push(0);
    for (pthread_t thread : this->thread_pool) {
        pthread_join(thread,NULL);
    }
}
