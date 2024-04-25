#include <pthread.h>
#include <stdio.h>

#include "world_loader.hpp"
#include "chunk.hpp"
#include "../game_loop/game_loop.hpp"

void* WorldLoader::meshingThread(void* data) {
    WorldLoader* parent = (WorldLoader*)data;

    while (!parent->die) {
        Chunk* chunk = parent->meshingQueue.pop();
        printf("meshing::got chunk!\n");
        if (parent->die || !chunk) return nullptr;
        chunk->gen_mesh();
        parent->genBufferQueue.push(chunk);
        printf("done meshing!\n");
    }

    return nullptr;
}

void* WorldLoader::genThread(void* data) {
    WorldLoader* parent = (WorldLoader*)data;

    while (!parent->die) {
        Chunk* chunk = parent->genQueue.pop();
        printf("gen::got chunk!\n");
        if (parent->die || !chunk) return nullptr;
        parent->worldGen.generateChunk(chunk);
        printf("here?\n");
        parent->meshingQueue.push(chunk);
        /*chunk->gen_mesh();
        printf("here\n");
        parent->genBufferQueue.push(chunk);*/
    }

    return nullptr;
}

void WorldLoader::meshChunk(Chunk* chunk) {
    this->meshingQueue.push(chunk);
}

void WorldLoader::genChunk(int pos[2]) {

    Chunk* chunk = new Chunk(this->world->gameLoop->program,this->world,pos);
    this->world->setChunk(pos,(Chunk*)-1l);

    this->genQueue.push(chunk);
}


WorldLoader::WorldLoader(World* world) {
    this->world = world;

    for (pthread_t thread : gen_thread_pool) {
        pthread_create(&thread,NULL,&WorldLoader::genThread,this);
    }
    for (pthread_t thread : mesh_thread_pool) {
        pthread_create(&thread,NULL,&WorldLoader::meshingThread,this);
    }
}

WorldLoader::~WorldLoader() {
    this->die = true;

    for (int i=0;i<NUM_GEN_THREADS;i++) this->genQueue.push(0);
    for (int i=0;i<NUM_MESHING_THREADS;i++) this->meshingQueue.push(0);

    for (pthread_t thread : this->gen_thread_pool) {
        pthread_join(thread,NULL);
    }

    for (pthread_t thread : this->mesh_thread_pool) {
        pthread_join(thread,NULL);
    }
}
