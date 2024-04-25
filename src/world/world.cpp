#include <unordered_map>

#include "world.hpp"
#include "chunk.hpp"
#include "../game_loop/game_loop.hpp"

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

World::World(GameLoop* gameLoop) {
    this->gameLoop = gameLoop;
    this->worldLoader = new WorldLoader(this);

}

World::~World() {
    delete this->worldLoader;
}
