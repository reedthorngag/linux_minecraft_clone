#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "chunk.hpp"
#include "blocks.hpp"


void Chunk::render() {
    
    GLuint model_loc = glGetUniformLocation(program, "model");
    GLuint tex_loc = glGetUniformLocation(program, "tex_offset");

    glBindVertexArray(this->VAO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //glDrawElements(GL_TRIANGLES, sizeof(Block::indices), GL_UNSIGNED_INT, NULL);
    //for (unsigned int i=0;i<count;i++)
    int old_block_id = -1;
    for (int n=0;n<CHUNK_HEIGHT; n++)
        if (layers[n]==nullptr) {
            for (int x=0;x<CHUNK_SIZE;x++) {
                for (int y=0;y<CHUNK_SIZE;y++) {
                    int block_id = this->solid_layers[n];

                    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, n, y));
                    glUniformMatrix4fv(model_loc,1,false,&model[0][0]);

                    for (short i=0;i<6;i++) {
                        if (block_id != old_block_id || texture_face_map[block_id][i])
                            glUniform1ui(tex_loc,texture_map[block_id]+texture_face_map[block_id][i]);
                        glDrawArrays(GL_TRIANGLE_STRIP, i*4 ,face_vertex_count);
                    }
                    old_block_id = block_id;
                }
            }
        }
}

void Chunk::gen_mesh() {

}

Chunk::Chunk(unsigned int program, glm::ivec2 pos) {
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


    glGenVertexArrays(1,&this->VAO);

    glGenBuffers(1,&this->VBO);
    //glGenBuffers(1,&this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Block::indices), Block::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glBindVertexArray(0);
}

Chunk::~Chunk() {

}




