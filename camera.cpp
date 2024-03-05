#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <stdio.h>

#include "camera.hpp"

Camera::Camera(unsigned int program) {
    this->updated = true;
    this->updateUniforms(program);
}

Camera::~Camera() {

}

void Camera::rotateX(int degrees) {
    this->updated = true;

    this->direction = glm::rotateY(this->direction,glm::radians((float)degrees));
}

void Camera::rotateY(int degrees) {
    this->updated = true;
    
    this->direction = glm::rotateX(this->direction,glm::radians((float)degrees));
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
    
    glm::vec3 origin = this->direction;
    origin += this->pos;

    glm::mat4 view = glm::lookAt(
        this->pos,
        origin,
        glm::vec3(0,1,0)
    );

	unsigned int lookAt = glGetUniformLocation(program,"view");
	glUniformMatrix4fv(lookAt, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 500.0f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}


