#include <unordered_map>

#include "world.hpp"

Chunk* ChunkMap::getChunk(int pos[2]) {
    std::string s;
    s += pos[0];
    s += ',';
    s += pos[1];
    return _chunks[s];
}

void ChunkMap::setChunk(int pos[2], Chunk* chunk) {
    std::string s;
    s += pos[0];
    s += ',';
    s += pos[1];
    _chunks[s] = chunk;
}

ChunkMap chunks;
