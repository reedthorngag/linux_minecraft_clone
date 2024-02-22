#include <glm/glm.hpp>

#include "block.hpp"

#ifndef _Chunk
#define _Chunk

const int CHUNK_HEIGHT = 10;
const int CHUNK_SIZE = 16;

struct block_data {
    short block_id;
    Block* block;
};

class Chunk {

    public:
        const block_data* layers[CHUNK_HEIGHT] = {0};
        const short solid_layers[CHUNK_HEIGHT] = {0};

        void render();

        Chunk(glm::ivec2 pos);
        ~Chunk();
};

#endif
