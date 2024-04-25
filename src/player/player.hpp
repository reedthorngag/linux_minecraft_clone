#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../globals.hpp"
#include "camera.hpp"
#include "../game_loop/input.hpp"

class Player {
    private:
        float gravity = base_gravity;
        Input* input;
    public:
        Camera* camera;

        void move(long long int ms);
        void tick();

        Player(GLuint program, Input* input);

};
