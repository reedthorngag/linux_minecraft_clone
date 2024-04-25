#include <unordered_map>

#include "world.hpp"
#include "chunk.hpp"

Chunk* World::getChunk(int pos[2]) {
    std::string s;
    s += pos[0];
    s += ',';
    s += pos[1];
    return _chunks[s];
}

void World::setChunk(int pos[2], Chunk* chunk) {
    std::string s;
    s += pos[0];
    s += ',';
    s += pos[1];
    _chunks[s] = chunk;
}
