#include <vector>
#include <unordered_map>
#include <string>

#include "chunk.hpp"

#ifndef _WORLD
#define _WORLD

class ChunkMap {
    public:
        std::unordered_map<std::string,Chunk*> chunks;

        void setChunk(int pos[2], Chunk* chunk) {
            std::string s;
            s += pos[0];
            s += ',';
            s += pos[1];
            chunks[s] = chunk;
        }
        Chunk* getChunk(int pos[2]) {
            std::string s;
            s += pos[0];
            s += ',';
            s += pos[1];
            return chunks[s];
        }
};

static ChunkMap chunks;


#endif