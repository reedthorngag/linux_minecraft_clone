#include <glm/glm.hpp>

#include "chunk.hpp"


void Chunk::render() {

}

Chunk::Chunk(glm::ivec2 pos) {
    (void)pos;
    
    for (int i=0;i<CHUNK_HEIGHT;i++) {
        this->layers[i] = new block_data[CHUNK_SIZE*CHUNK_SIZE];
    }

}

Chunk::~Chunk() {

}




