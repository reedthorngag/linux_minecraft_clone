#include <stdio.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../world/chunk.hpp"
#include "../world/world.hpp"
#include "../world/generation/world_gen.hpp"
#include "../world/world_loader.hpp"

#include "../player/camera.hpp"
#include "../player/player.hpp"

#include "../startup/window.hpp"

#include "menu.hpp"
#include "input.hpp"

class GameLoop {
    private:
        bool running = false;
        bool _exit = false;
        bool paused = false;

        bool playerActive = true;

        Clock::time_point lastTick;

        World* world;
        Menu menu;
        Input input;
        Player* player;
        Camera* freeCam;

        Camera* activeCamera;

    public:
        GLuint program;

        GameLoop();

        void start();
        void pause();
        void unpause();
        void kill();
        void showMenu();

        void render(long long int ms);
        void tick();
        void generateChunks();
};


