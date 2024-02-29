#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <string>

#include "chunk.hpp"
#include "blocks.hpp"

void Chunk::render() {
    
    GLuint model_loc = glGetUniformLocation(program, "model");

    glm::mat4 model = glm::translate(glm::mat4(1.0),this->pos);

    glUniformMatrix4fv(model_loc,1,false,&model[0][0]);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES)/sizeof(unsigned int), INDICES, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glDrawElements(GL_TRIANGLES, count*2*3, GL_UNSIGNED_INT, NULL);
}

void Chunk::add_face(std::vector<face*>* _faces,short pos[3],faces _face) {
    short block_id = this->layers[pos[2]]==nullptr? this->solid_layers[pos[2]] : this->layers[pos[2]][pos[1]*CHUNK_SIZE+pos[0]];

    face* face = new struct face;

    memcpy(face->face_data,(float*)((long)CUBE_VERTICES+face_offset[_face]),DATA_SIZE);

    int tex_pos = texture_map[block_id];

    for (short i=0;i<4;i++) {
        face->face_data[i*VERTEX_SIZE+(sizeof(float)*3)] += tex_pos+texture_face_map[block_id][i];
    }

    face->indices = (unsigned int*)&INDICES[_face*6];
    
    _faces->push_back(face);
}

void Chunk::gen_mesh() {
    std::vector<face*> faces;
    for (short x=0;x<CHUNK_SIZE;x++) {
        for (short y=0;y<CHUNK_SIZE;y++) {
            short height = this->heightmap[y*CHUNK_SIZE+x];

            short pos[3]{x,y,height};

            this->add_face(&faces,pos,faces::TOP);
        }
    }

    int count = faces.size();
    float* vertices = new float[count*5*4];
    unsigned int* indices = new unsigned int[count*6];

    float* _vertices = vertices;
    unsigned int* _indices = indices;

    for (face* face : faces) {
        memcpy(_vertices,face->face_data,DATA_SIZE);
        _vertices += 5 * 4;

        memcpy(_indices,face->indices,sizeof(unsigned int) * 6);
        _indices += 6;

        for (int i=0;i<4;i++) {
            printf("%f, %f, %f,  %f, %f,\n",vertices[i*5+0],vertices[i*5+1],vertices[i*5+2],vertices[i*5+3],vertices[i*5+4]);
        }

        printf("%u, %u, %u,  %u, %u, %u\n",face->indices[0],face->indices[1],face->indices[2],face->indices[3],face->indices[4],face->indices[5]);

        delete face;
    }

    this->count = count;

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, count * DATA_SIZE, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    printf("4\n");

    delete vertices;
    delete indices;
    printf("5\n");
}

Chunk::Chunk(unsigned int program, glm::vec3 pos) {
    (void)program;
    (void)pos;

    this->program = program;
    this->pos = pos;

    for (int i=0;i<CHUNK_HEIGHT;i++) {
        this->layers[i] = nullptr;
        this->solid_layers[i] = blocks::DIRT;
    }

    this->solid_layers[0] = blocks::STONE;
    this->solid_layers[CHUNK_HEIGHT-1] = blocks::GRASS;

    for (int i=0;i<CHUNK_SIZE*CHUNK_SIZE;i++) {
        this->heightmap[i] = CHUNK_HEIGHT-1;
    }

    glGenVertexArrays(1,&this->VAO);

    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glBindVertexArray(0);

    gen_mesh();
}

Chunk::~Chunk() {

}




