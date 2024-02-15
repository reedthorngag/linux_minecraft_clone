#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <stdio.h>

#include "camera.hpp"

Camera::Camera(unsigned int program) {
    this->updated = true;
    this->updateUniforms(program);
}

Camera::~Camera() {

}

void Camera::rotate(int degreesX, int degreesY) {
    this->updated = true;
    this->rotationX += degreesX;
    if (this->rotationX >= 360)
        this->rotationX -= 360;
    
    this->rotationY += degreesY;
    if (this->rotationY >= 360)
        this->rotationY -= 360;
}


void Camera::move(glm::vec3 offset) {
    this->updated = true;
    this->pos += offset;
}

void Camera::updateFOV(int FOV) {
    this->updated = true;
    (void)FOV;
    // TODO: work out how to change the FOV
}

void Camera::updateUniforms(unsigned int program) {
    if (!this->updated) return;
    glm::mat4 view;
    view = glm::translate(glm::mat4(1.0), this->pos);
    view = glm::rotate(view,glm::radians((float)this->rotationX),glm::vec3(0,1,0));
    view = glm::rotate(view,glm::radians((float)this->rotationY),glm::vec3(1,0,0));
	unsigned int lookAt = glGetUniformLocation(program,"view");
	glUniformMatrix4fv(lookAt, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}


