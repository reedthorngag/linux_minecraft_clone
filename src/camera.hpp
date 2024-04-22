#include <glm/glm.hpp>

class Camera {

    public:
        glm::vec3 pos;
        glm::vec3 origin;
        glm::vec3 direction;
        int rotationX = 0;
        int rotationY = 0;
        glm::mat4 perspective;
        bool updated;

        void rotateX(int degrees);
        void rotateY(int degrees);

        void move(glm::vec3 movement);

        void updateFOV(int FOV); // default 100

        void updateUniforms(unsigned int program);

        Camera(unsigned int program);
        ~Camera();
};



