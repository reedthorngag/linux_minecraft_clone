#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../globals.hpp"
#include "camera.hpp"

class Player {
    private:
        float gravity = base_gravity;
    public:
        Camera* camera;

        Player(GLuint program);

};
