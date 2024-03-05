#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <string>

#include "chunk.hpp"
#include "blocks.hpp"
#include "world.hpp"

extern ChunkMap chunks;

void Chunk::render() {

    glUseProgram(this->program);
    
    GLuint model_loc = glGetUniformLocation(program, "model");

    glm::mat4 model = glm::translate(glm::mat4(1.0),glm::vec3(this->pos[0]*CHUNK_SIZE,0,this->pos[1]*CHUNK_SIZE));

    glUniformMatrix4fv(model_loc,1,false,&model[0][0]);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glDrawElements(GL_TRIANGLES, this->count * 6, GL_UNSIGNED_INT, NULL);
}

short Chunk::get_block(short pos[3]) {
    return this->layers[pos[1]]==nullptr ? this->solid_layers[pos[1]] : this->layers[pos[1]][pos[2]*CHUNK_SIZE+pos[0]];
}

void Chunk::add_face(std::vector<face*>* _faces,short pos[3],faces _face) {
    short block_id = this->get_block(pos);

    face* face = new struct face;

    memcpy(face->face_data,(float*)((long)CUBE_VERTICES+face_offset[_face]),DATA_SIZE);

    for (int i=0;i<4;i++) {
        for (int j=0;j<3;j++) {
            face->face_data[i*5+j] += pos[j];
        }
    }

    int tex_pos = texture_map[block_id];

    for (short i=0;i<4;i++) {
        face->face_data[i*5+3] += tex_pos+texture_face_map[block_id][_face];
    }
    
    _faces->push_back(face);
}

void Chunk::gen_mesh() {
    std::vector<face*> faces;
    for (short x=0;x<CHUNK_SIZE;x++) {
        for (short z=0;z<CHUNK_SIZE;z++) {
            for (short y=this->heightmap[z*CHUNK_SIZE+x]; y>=0; y--) {

                short pos[3] {x,y,z};

                bool block = false;
                if (pos[0]-1 < 0) {
                    int chunkpos[2]{this->pos[0]-1,this->pos[1]};

                    Chunk* chunk = chunks.getChunk(chunkpos);
                    if (chunk) {
                        short blockpos[3] {CHUNK_SIZE-1,y,z};
                        block = chunk->get_block(blockpos);
                    }
                } else {
                    short chunkpos[3]{(short)(x-1),y,z};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::WEST);
                }

                block = false;
                if (pos[0]+1 == CHUNK_SIZE) {
                    int chunkpos[2]{this->pos[0]+1,this->pos[1]};

                    Chunk* chunk = chunks.getChunk(chunkpos);
                    if (chunk) {
                        short blockpos[3] {0,y,z};
                        block = chunk->get_block(blockpos);
                    }
                } else {
                    short chunkpos[3]{(short)(x+1),y,z};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::EAST);
                }

                block = false;
                if (pos[2]-1 < 0) {
                    int chunkpos[2]{this->pos[0],this->pos[1]-1};

                    Chunk* chunk = chunks.getChunk(chunkpos);
                    if (chunk) {
                        short blockpos[3] {x,y,CHUNK_SIZE-1};
                        block = chunk->get_block(blockpos);
                    }
                } else {
                    short chunkpos[3]{x,y,(short)(z-1)};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::SOUTH);
                }

                block = false;
                if (pos[2]+1 == CHUNK_SIZE) {
                    int chunkpos[2]{this->pos[0],this->pos[1]+1};

                    Chunk* chunk = chunks.getChunk(chunkpos);
                    if (chunk) {
                        short blockpos[3] {x,y,0};
                        block = chunk->get_block(blockpos);
                    }
                } else {
                    short chunkpos[3]{x,y,(short)(z+1)};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::NORTH);
                }

                block = false;
                if (pos[1]-1 >= 0) {
                    short chunkpos[3]{x,(short)(y-1),z};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::BOTTOM);
                }

                block = false;
                if (pos[1]+1 < CHUNK_HEIGHT) {
                    short chunkpos[3]{x,(short)(y+1),z};
                    block = this->get_block(chunkpos);
                }
                if (!block) {
                    this->add_face(&faces,pos,faces::TOP);
                }
            }
        }
    }

    int count = faces.size();
    float* vertices = new float[count*5*4];
    unsigned int* indices = new unsigned int[count*6];

    float* _vertices = vertices;
    unsigned int* _indices = indices;

    int n=0;
    for (face* face : faces) {
        memcpy(_vertices,face->face_data,DATA_SIZE);
        _vertices += 5 * 4;

        for (short i = 0; i<6; i++) {
            face->indices[i] += n;
        }
        n += 3;

        memcpy(_indices,face->indices,sizeof(unsigned int) * 6);
        _indices += 6;

        
        /*for (int i=0;i<4;i++) {
            printf("%f, %f, %f,  %f, %f,\n",vertices[i*5+0],vertices[i*5+1],vertices[i*5+2],vertices[i*5+3],vertices[i*5+4]);
        }

        printf("%u, %u, %u,  %u, %u, %u\n",face->indices[0],face->indices[1],face->indices[2],face->indices[3],face->indices[4],face->indices[5]);
        */

        delete face;
        n++;
    }

    this->count = count;

    glUseProgram(this->program);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, count * 5 * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

    delete vertices;
    delete indices;
}

Chunk::Chunk(unsigned int program, int pos[2]) {
    this->program = program;
    this->pos = pos;

    glUseProgram(this->program);

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
}

Chunk::~Chunk() {
    delete this->pos;
}




