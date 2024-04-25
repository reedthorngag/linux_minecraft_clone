#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <vector>
#include <string>
#include <stdio.h>

#include "blocks.hpp"
#include "world.hpp"
#include "../globals.hpp"

#ifndef _Chunk
#define _Chunk

const int VERTEX_SIZE = sizeof(float)*(3+2);
const int DATA_SIZE = VERTEX_SIZE*4;

struct face {
    float face_data[DATA_SIZE]; // 3 * float vertices + 2 * float tex coords * 4
    unsigned int indices[6] {0,1,2, 1,2,3};
};

class Chunk {

    private:
        GLuint program;
        World* world;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        float* vertices;
        unsigned int* indices;
        unsigned int _count;

        unsigned int count = 0;

        void add_face(std::vector<face*>* _faces,short pos[3],faces _face);

    public:
        bool ready = false;

        short* layers[CHUNK_HEIGHT] = {0};
        short solid_layers[CHUNK_HEIGHT] = {0};

        int* pos;

        short heightmap[CHUNK_SIZE*CHUNK_SIZE] = { 0 };

        void render();
        void gen_mesh();
        void genBuffers(World* world);
        short get_block(short pos[3]);

        Chunk(GLuint program, World* world, int pos[2]);
        ~Chunk();
};

#endif
