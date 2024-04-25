#include <vector>
#include <unordered_map>
#include <string>

#include "world_loader.hpp"
#include "../globals.hpp"

#ifndef _WORLD
#define _WORLD

struct Chunk;

class World {
    public:
        std::unordered_map<std::string,Chunk*> _chunks;

        WorldLoader worldLoader;

        void setChunk(int pos[2], Chunk* chunk);
        Chunk* getChunk(int pos[2]);

};

#endif