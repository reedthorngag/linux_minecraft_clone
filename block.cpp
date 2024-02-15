#include <GL/glew.h>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "block.hpp"

const float Block::vertices[]{
    -0.5, 0.0, 0.0, // 0 bottom left front
    -0.5, 1.0, 0.0, // 1 top left front
    0.5,  0.0, 0.0, // 2 bottom right front
    0.5,  1.0, 0.0, // 3 top right front
    -0.5, 0.0, -1.0, // 4 bottom left back
    -0.5, 1.0, -1.0, // 5 top left back
    0.5,  0.0, -1.0, // 6 bottom right back
    0.5,  1.0, -1.0, // 7 top right back
};
const unsigned int Block::indices[]{
    0,1,2,
    2,1,3,
    4,5,6,
    6,5,7,
    0,4,5,
    0,1,5
};


void Block::render(unsigned int program) {
    glm::mat4 model = glm::mat4(1.0);//glm::translate(glm::mat4(1.0f), glm::vec3(1, 1, 1));
    //const float model[] = {1,1,1,1};
    glUniformMatrix4fv(glGetUniformLocation(program, "model"),1,false,&model[0][0]);
    printf("error: %d\n",glGetError());

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glDrawElements(GL_TRIANGLES, sizeof(Block::indices), GL_UNSIGNED_INT, NULL);

}

Block::Block() {
    glGenVertexArrays(1,&this->VAO);

    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Block::vertices), Block::vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Block::indices), Block::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glBindVertexArray(0);

}

Block::~Block() {
}
