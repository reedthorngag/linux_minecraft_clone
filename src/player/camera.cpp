#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <stdio.h>

#include "camera.hpp"

Camera::Camera(GLuint program,glm::vec3 startPos) {
    this->updated = true;
    this->pos = startPos;
    this->program = program;
    this->updateUniforms();
}

Camera::~Camera() {

}

void Camera::rotateX(int degrees) {
    this->updated = true;
    this->rotationY += degrees;  // because its around, not along, that axis
    this->direction = glm::rotateX(glm::vec3(0,0,1),glm::radians((float)this->rotationX));
    this->direction = glm::rotateY(this->direction,glm::radians((float)this->rotationY));
}

void Camera::rotateY(int degrees) {
    this->updated = true;
    if (this->rotationX+degrees < -90 || this->rotationX+degrees > 90) return;
    this->rotationX += degrees; // because its around, not along, that axis
    this->direction = glm::rotateX(glm::vec3(0,0,1),glm::radians((float)this->rotationX));
    this->direction = glm::rotateY(this->direction,glm::radians((float)this->rotationY));
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

void Camera::updateUniforms() {
    //if (!this->updated) return;
    
    glm::vec3 origin = this->direction;
    origin += this->pos;

    glm::mat4 view = glm::lookAt(
        this->pos,
        origin,
        glm::vec3(0,1,0)
    );

	unsigned int lookAt = glGetUniformLocation(this->program,"view");
	glUniformMatrix4fv(lookAt, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 500.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}


