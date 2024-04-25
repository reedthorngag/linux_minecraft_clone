#include <glm/glm.hpp>

#ifndef _CAMERA
#define _CAMERA

class Camera {

    public:
        glm::vec3 pos;
        glm::vec3 origin;
        glm::vec3 direction = glm::vec3(0,0,1);
        int rotationX = 0;
        int rotationY = 0;
        glm::mat4 perspective;
        GLuint program;
        bool updated;

        void rotateX(int degrees);
        void rotateY(int degrees);

        void move(glm::vec3 movement);

        void updateFOV(int FOV); // default 100

        void updateUniforms();

        Camera(GLuint program, glm::vec3 startPos);
        ~Camera();
};

#endif

