

#include "../world/chunk.hpp"
#include "../world/world.hpp"
#include "../world/generation/world_gen.hpp"
#include "../world/world_loader.hpp"

#include "../player/camera.hpp"
#include "../player/player.hpp"

#include "menu.hpp"
#include "input.hpp"

class GameLoop {
    private:
        bool running = false;
        bool exit = false;
        bool paused = false;

        Clock::time_point lastTick;

        World world;
        Menu menu;
        Input input;
        Player player;
        Camera camera;

    public:
        void start();
        void pause();
        void unpause();
        void kill();
        void showMenu();

        void tick();
};


