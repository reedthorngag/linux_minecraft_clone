

#include "game_loop.hpp"


void GameLoop::start() {
    this->running = true;
}

void GameLoop::tick() {
    this->lastTick = Clock::now();

    if (keys[25]) // w
        camera.move(camera.direction * (glm::vec3(speed,speed,speed) * glm::vec3(keys[50]?speed_scale:1)));
    
    if (keys[38]) // a
        camera.move(glm::cross(glm::vec3(0,1,0),camera->direction*(glm::vec3(speed,speed,speed)*glm::vec3(keys[50]?speed_scale:1))));

    if (keys[39]) // s
        camera.move(-camera->direction*(glm::vec3(speed,speed,speed)*glm::vec3(keys[50]?speed_scale:1)));
    
    if (keys[40]) // d
        camera.move(glm::cross(glm::vec3(0,1,0),-camera->direction*(glm::vec3(speed,speed,speed)*glm::vec3(keys[50]?speed_scale:1))));


    if (keys[111]) // up
        camera.rotateY(-1);
    
    if (keys[116]) // down
        camera.rotateY(1);

    if (keys[113]) // left
        camera.rotateX(1);
    
    if (keys[114]) // right
        camera.rotateX(-1);
}

void GameLoop::pause() {
    this->paused = true;
}

void GameLoop::unpause() {
    this->paused = false;
}

void GameLoop::kill() {
    this->running = false;
    this->exit = true;
}

void GameLoop::showMenu() {
    this->menu.giveControl();
}
