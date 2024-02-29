#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include "blocks.hpp"

#ifndef _Chunk
#define _Chunk

const int CHUNK_HEIGHT = 1;
const int CHUNK_SIZE = 1;


const int VERTEX_SIZE = sizeof(float)*(3+2);
const int DATA_SIZE = VERTEX_SIZE*4;

struct face {
    float face_data[DATA_SIZE]; // 3 * float vertices + 2 * float tex coords * 4
    unsigned int* indices;
};

class Chunk {

    public:
        short* layers[CHUNK_HEIGHT] = {0};
        short solid_layers[CHUNK_HEIGHT] = {0};

        GLuint program;
        glm::vec3 pos;

        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        float* vertice_data;
        unsigned int* indice_data;
        unsigned int count = 0;

        short heightmap[CHUNK_SIZE*CHUNK_SIZE] = { 0 };

        void render();
        void add_face(std::vector<face*>* _faces,short pos[3],faces _face);
        void gen_mesh();

        Chunk(unsigned int program, glm::vec3 pos);
        ~Chunk();
};

#endif
