#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "chunk.hpp"
#include "blocks.hpp"


void Chunk::render() {
    glm::mat4 model = glm::mat4(1.0);//glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 1));
    //const float model[] = {1,1,1,1};
    glUniformMatrix4fv(glGetUniformLocation(program, "model"),1,false,&model[0][0]);

    GLuint tex_loc = glGetUniformLocation(program, "tex_offset");

    glBindVertexArray(this->VAO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //glDrawElements(GL_TRIANGLES, sizeof(Block::indices), GL_UNSIGNED_INT, NULL);
    //for (unsigned int i=0;i<count;i++) 
    for (short i=0;i<6;i++) {
        glUniform1ui(tex_loc,1+texture_map[1][i]);
        glDrawArrays(GL_TRIANGLE_STRIP, i*4 ,face_vertex_count);
    }
}

void Chunk::gen_mesh() {

}

Chunk::Chunk(unsigned int program, glm::ivec2 pos) {
    (void)program;
    (void)pos;

    this->program = program;
    this->pos = pos;
    
    for (int i=1;i<CHUNK_HEIGHT-2;i++) {
        this->layers[i] = nullptr;
        this->solid_layers[i] = 1;
    }


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




