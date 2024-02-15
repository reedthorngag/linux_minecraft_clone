#include <glm/glm.hpp>

class Camera {

    public:
        glm::vec3 pos;
        int rotationX;
        int rotationY;
        glm::mat4 perspective;
        bool updated;

        void rotate(int degreesX, int degreesY);

        void move(glm::vec3 movement);

        void updateFOV(int FOV); // default 100

        void updateUniforms(unsigned int program);

        Camera(unsigned int program);
        ~Camera();
};



