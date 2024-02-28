#include <glm/glm.hpp>
#include <GL/glew.h>

#include "block.hpp"

#ifndef _Chunk
#define _Chunk

const int CHUNK_HEIGHT = 10;
const int CHUNK_SIZE = 100;

struct block_data {
    short block_id;
    glm::uvec3 pos;
};

struct face_data {
    int offset;
    short tex_offset;
};

class Chunk {

    public:
        const short* layers[CHUNK_HEIGHT] = {0};
        short solid_layers[CHUNK_HEIGHT] = {0};

        GLuint program;
        glm::ivec2 pos;

        GLuint VAO;
        GLuint VBO;
        unsigned char* mesh_data;
        unsigned int* offsets;
        unsigned int count;

        void render();
        void gen_mesh();

        Chunk(unsigned int program, glm::ivec2 pos);
        ~Chunk();
};

#endif
