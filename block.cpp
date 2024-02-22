#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "block.hpp"
#include "blocks.hpp"

const float Block::vertices[]{
    0, 0.0, 0.0,    0, 0, // 0 bottom right front
    0, 1.0, 0.0,    0.007, 0, // 1 top right front
    1, 0.0, 0.0,    0, 0.01, // 2 bottom left front
    1, 1.0, 0.0,    0.007, 0.01, // 3 top left front
    0, 0.0, 1,      0, 0.01, // 4 bottom right back
    0, 1.0, 1,      0.007, 0.01, // 5 top right back    
    1, 0.0, 1.0,    0, 0, // 6 bottom left back
    1, 1.0, 1.0,    0.007, 0, // 7 top left back
};
const unsigned int Block::indices[]{
    0,1,2,
    2,1,3,
    4,5,6,
    6,5,7,
    0,1,5,
    0,4,5,
    2,6,7,
    2,3,7,
    1,3,7,
    5,7,1
};


void Block::render(unsigned int program) {
    glm::mat4 model = glm::mat4(1.0);//glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 1));
    //const float model[] = {1,1,1,1};
    glUniformMatrix4fv(glGetUniformLocation(program, "model"),1,false,&model[0][0]);

    glUniform1ui(glGetUniformLocation(program, "tex_offset"),3);

    glBindVertexArray(this->VAO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    //glDrawElements(GL_TRIANGLES, sizeof(Block::indices), GL_UNSIGNED_INT, NULL);
    glDrawArrays(GL_TRIANGLE_STRIP,face_offset::NORTH,face_vertex_count);

}

Block::Block() {
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

Block::~Block() {
}
