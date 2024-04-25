#include <stdlib.h>

#include "game_loop.hpp"

GameLoop::GameLoop(GLuint program) {
    this->program = program;
    this->freeCam = new Camera(this->program,glm::vec3(0,100,0));
    this->world = new World(this);
    this->player = new Player(this->program,&this->input);
}

void GameLoop::start() {
    this->activeCamera = this->player->camera;
    this->running = true;

    std::chrono::time_point end = Clock::now();
    std::chrono::time_point oldNow = Clock::now();

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
                                    this->world->worldLoader->meshChunk(this->world->getChunk(pos));
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
            std::unique_lock<std::mutex> lock(this->world->worldLoader->genBufferQueue.mutex);
            while (!this->world->worldLoader->genBufferQueue.queue.empty()) {
                printf("genning buffer\n");
                this->world->worldLoader->genBufferQueue.queue.front()->genBuffers(this->world);
                this->world->worldLoader->genBufferQueue.queue.pop();
            }
        }

        std::chrono::time_point now = Clock::now();
        render(std::chrono::duration_cast<std::chrono::milliseconds>(now-oldNow).count());
        oldNow = now;

        end = Clock::now();
        long long int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        //if (ms) printf("\r ms: %d, fps: %d      \r",(int)ms, (int)(1000/ms));
    }
}

void GameLoop::render(long long int ms) {
    if (this->playerActive) this->player->move(ms);

    glClearColor(0.0, 0.65, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->activeCamera->updateUniforms();

    int posX = ((long)this->activeCamera->pos[0])/CHUNK_SIZE;
    int posY = ((long)this->activeCamera->pos[2])/CHUNK_SIZE;

    for (int x=posX-RENDER_DISTANCE; x<=posX+RENDER_DISTANCE; x++) {
        for (int y=posY-RENDER_DISTANCE;y<=posY+RENDER_DISTANCE;y++) {
            int pos[2]{x,y};
            Chunk* chunk = this->world->getChunk(pos);
            if (chunk && (long)chunk!=-1l) chunk->render();
        }
    }

    glXSwapBuffers(dpy, win);
}

void GameLoop::generateChunks() {
    int posX = ((long)this->activeCamera->pos[0])/CHUNK_SIZE;
    int posY = ((long)this->activeCamera->pos[2])/CHUNK_SIZE;

    for (short i=0;i>-2;i--) {
        for (int n=0;n<RENDER_DISTANCE; n++) {
            int pos[2]{posX,posY+(n*i)};

            if (!this->world->getChunk(pos)) {
                for (int x=posX-RENDER_DISTANCE;x<=posX+RENDER_DISTANCE;x++) {
                    pos[0] = x;
                    if (!this->world->getChunk(pos)) {
                        int* p = new int[2]{pos[0],pos[1]};
                        this->world->setChunk(p,(Chunk*)-1L);
                        this->world->worldLoader->genChunk(p);
                    }
                }
            }
        }
    }

    for (short i=0;i>-2;i--) {
        for (int n=0;n<RENDER_DISTANCE; n++) {
            int pos[2]{posX+(n*i),posY};

            if (!this->world->getChunk(pos)) {
                for (int y=posY-RENDER_DISTANCE;y<=posY+RENDER_DISTANCE;y++) {
                    pos[1] = y;
                    if (!this->world->getChunk(pos)) {
                        int* p = new int[2]{pos[0],pos[1]};
                        this->world->setChunk(p,(Chunk*)-1L);
                        this->world->worldLoader->genChunk(p);
                    }
                }
            }
        }
    }
}

void GameLoop::tick() {
    this->lastTick = Clock::now();

    if (this->playerActive) this->player->tick();

    this->generateChunks();
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
