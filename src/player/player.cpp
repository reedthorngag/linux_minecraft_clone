#include "player.hpp"


void Player::move(long long int ms) {
    glm::vec3 move_speed = glm::vec3(speed,speed,speed) * glm::vec3((this->input->keys[50]?speed_scale:1) * ms);

    if (this->input->keys[25]) // w
        this->camera->move(this->camera->direction * move_speed);
    
    if (this->input->keys[38]) // a
        this->camera->move(glm::cross(glm::vec3(0,1,0),this->camera->direction*move_speed));

    if (this->input->keys[39]) // s
        this->camera->move(-this->camera->direction*move_speed);
    
    if (this->input->keys[40]) // d
        this->camera->move(glm::cross(glm::vec3(0,1,0),-this->camera->direction*move_speed));


    if (this->input->keys[111]) // up
        this->camera->rotateY(-1);
    
    if (this->input->keys[116]) // down
        this->camera->rotateY(1);

    if (this->input->keys[113]) // left
        this->camera->rotateX(1);
    
    if (this->input->keys[114]) // right
        this->camera->rotateX(-1);
}

void Player::tick() {

}

Player::Player(GLuint program, Input* input) {
    this->input = input;
    this->camera = new Camera(program,glm::vec3(0,100,0));
}

