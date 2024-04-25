

#include "player.hpp"

Player::Player(GLuint program) {
    this->camera = new Camera(program,glm::vec3(0,100,0));
}

