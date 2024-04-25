#include <stdlib.h>

#include "game_loop.hpp"

GameLoop::GameLoop() {
    this->freeCam = new Camera(this->program,glm::vec3(0,100,0));
}

void GameLoop::start() {
    this->activeCameraController = this->player->camera;
    this->running = true;
    while(running && !paused) {
        if (XCheckWindowEvent(dpy,win,mask,&xev)) {
            switch (xev.type) {
                case KeyPress:
                    input.press(xev.xkey.keycode);
                    break;
                case KeyRelease:
                    input.release(xev.xkey.keycode);
                    switch (xev.xkey.keycode) {
                        case 9:
                            GameLoop::kill();
                            break;
                        
                        case 27: // r
                            {
                            std::chrono::time_point start1 = Clock::now();
                            for (int x=-(RENDER_DISTANCE/2); x<(RENDER_DISTANCE/2); x++) {
                                for (int y=-(RENDER_DISTANCE/2);y<(RENDER_DISTANCE/2);y++) {
                                    int pos[2]{x,y};
                                    this->world->worldLoader.pushChunk(this->world->getChunk(pos));
                                }
                            }
                            std::chrono::time_point end1 = Clock::now();
                            long long int ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1-start1).count();
                            printf("\n total chuck mesh time: %dms  \n",(int)ms1);
                            }
                            break;

                        default:
                            printf("keycode: %d\n",xev.xkey.keycode);
                            break;
                    }

                case MotionNotify:
                    //if (xev.xmotion.x==halfWidth && xev.xmotion.y==halfHeight) break;                
                    //printf("pointer: x %d, y %d\n",xev.xmotion.x-halfWidth,xev.xmotion.y-halfHeight);
                    break;
            }
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - lastTick).count() > tickTime)
            tick();
        
        std::chrono::time_point start = Clock::now();
        {
            std::unique_lock<std::mutex> lock(this->world->worldLoader.genBufferQueue.mutex);
            while (!this->world->worldLoader.genBufferQueue.queue.empty()) {
                this->world->worldLoader.genBufferQueue.queue.front()->genBuffers();
                this->world->worldLoader.genBufferQueue.queue.pop();
            }
        }
        render();
        std::chrono::time_point end = Clock::now();
        long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        if (ms)
            printf("\r ms: %d, fps: %d      \r",(int)ms, (int)(1000/ms));
    }
}

void GameLoop::render() {
    glClearColor(0.0, 0.65, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->activeCameraController->updateUniforms();

    for (int x=-(RENDER_DISTANCE/2); x<(RENDER_DISTANCE/2); x++) {
        for (int y=-(RENDER_DISTANCE/2);y<(RENDER_DISTANCE/2);y++) {
            int pos[2]{x,y};
            this->world->getChunk(pos)->render();
        }
    }

    glXSwapBuffers(dpy, win);
}

void GameLoop::generateChunks() {
    
}

void GameLoop::tick() {
    this->lastTick = Clock::now();

    if (this->input.keys[25]) // w
        this->activeCameraController->move(this->activeCameraController->direction * (glm::vec3(speed,speed,speed) * glm::vec3(this->input.keys[50]?speed_scale:1)));
    
    if (this->input.keys[38]) // a
        this->activeCameraController->move(glm::cross(glm::vec3(0,1,0),this->activeCameraController->direction*(glm::vec3(speed,speed,speed)*glm::vec3(this->input.keys[50]?speed_scale:1))));

    if (this->input.keys[39]) // s
        this->activeCameraController->move(-this->activeCameraController->direction*(glm::vec3(speed,speed,speed)*glm::vec3(this->input.keys[50]?speed_scale:1)));
    
    if (this->input.keys[40]) // d
        this->activeCameraController->move(glm::cross(glm::vec3(0,1,0),-this->activeCameraController->direction*(glm::vec3(speed,speed,speed)*glm::vec3(this->input.keys[50]?speed_scale:1))));


    if (this->input.keys[111]) // up
        this->activeCameraController->rotateY(-1);
    
    if (this->input.keys[116]) // down
        this->activeCameraController->rotateY(1);

    if (this->input.keys[113]) // left
        this->activeCameraController->rotateX(1);
    
    if (this->input.keys[114]) // right
        this->activeCameraController->rotateX(-1);
}

void GameLoop::pause() {
    this->paused = true;
}

void GameLoop::unpause() {
    this->paused = false;
}

void GameLoop::kill() {
    this->running = false;
    this->_exit = true;
    glDeleteProgram(program);
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, glc);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    exit(0);
}

void GameLoop::showMenu() {
    this->menu.giveControl();
}
