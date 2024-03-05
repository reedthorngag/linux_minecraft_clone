#include <vector>
#include <unordered_map>
#include <string>

#include "chunk.hpp"

#ifndef _WORLD
#define _WORLD

const int RENDER_DISTANCE = 24;

class ChunkMap {
    public:
        std::unordered_map<std::string,Chunk*> _chunks;

        void setChunk(int pos[2], Chunk* chunk);
        Chunk* getChunk(int pos[2]);
};

extern ChunkMap chunks;

#endif