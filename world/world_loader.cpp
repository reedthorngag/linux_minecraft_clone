#include <pthread.h>

#include "world_loader.hpp"

void* WorldLoader::thread(void* data) {
    WorldLoader* parent = (WorldLoader*)data;


}


WorldLoader::WorldLoader() {
    for (pthread_t thread : thread_pool) {
        pthread_create(&thread,NULL,&WorldLoader::thread,this);
    }
}

WorldLoader::~WorldLoader() {
    for (pthread_t thread : this->thread_pool) {
        pthread_join(thread,NULL);
    }
}
