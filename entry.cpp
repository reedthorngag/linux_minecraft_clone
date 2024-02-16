#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/xfixesproto.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.hpp"
#include "block.hpp"
#include "camera.hpp"

int width = 800;
int height = 600;

int halfWidth = width/2;
int halfHeight = height/2;

typedef std::chrono::high_resolution_clock Clock;
Clock::time_point lastTick;
int tickTime = 10;


Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

bool keys[255];

std::vector<Block*> blocks;

unsigned int indices[] {
    0,1,2
};
float vertices[] = {
    0.0, 1.0, -0.1,
    0.5, 0.0, -0.1,
    -0.5,0.0, -0.1
};

GLuint program;
Camera* camera;

unsigned int VBO;
unsigned int VAO;
unsigned int EBO;

int imgWidth, imgHeight, nrChannels;
unsigned char *imgData = stbi_load("textures/block_textures.png", &imgWidth, &imgHeight, &nrChannels, 0);


void DebugCallbackARB(GLenum source,
                      GLenum type,
                      GLuint id,
                      GLenum severity,
                      GLsizei length,
                      const GLchar* message,
                      const GLvoid* userParam) {
    (void)source;
    (void)type;
    (void)id;
    (void)severity;
    (void)length;
    (void)userParam;
    printf("debug callback: %s\n",message);
}

void tick() {
    lastTick = Clock::now();

    // doesnt seem to make a noticible difference the order rotations and translations are applied

    if (keys[25]) // w
        camera->move(camera->direction*glm::vec3(0.075,0.075,0.075));
        //camera->move(glm::vec3(0,0,0.1));
    
    if (keys[38]) // a
        camera->move(glm::cross(glm::vec3(0,1,0),camera->direction*glm::vec3(0.075,0.075,0.075)));

    if (keys[39]) // s
        camera->move(-camera->direction*glm::vec3(0.075,0.075,0.075));
    
    if (keys[40]) // d
        camera->move(glm::cross(glm::vec3(0,1,0),-camera->direction*glm::vec3(0.075,0.075,0.075)));


    if (keys[111]) // up
        camera->rotateY(-1);
    
    if (keys[116]) // down
        camera->rotateY(1);

    if (keys[113]) // left
        camera->rotateX(1);
    
    if (keys[114]) // right
        camera->rotateX(-1);
}

void render() {
    glClearColor(0.0, 0.65, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->updateUniforms(program);

    for (Block* block : blocks) {
        block->render(program);
    }

    glXSwapBuffers(dpy, win);
} 

int main() {
    
    dpy = XOpenDisplay(NULL);
 
    if(dpy == NULL) {
        printf("\n\tcannot connect to X server\n\n");
        return 1;
    }

    root = DefaultRootWindow(dpy);

    vi = glXChooseVisual(dpy, 0, att);

    if(vi == NULL) {
        printf("\n\tno appropriate visual found\n\n");
            return 1;
    } 
    else {
        printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
    }

    cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

    long mask = KeyPressMask
                | KeyReleaseMask
                | ButtonPressMask
                | ButtonReleaseMask
                | PointerMotionMask;

    swa.colormap = cmap;
    swa.event_mask = mask;
    swa.cursor = None;
    


    win = XCreateWindow(dpy, root, 0, 0, width, height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask | CWCursor, &swa);

    XMapWindow(dpy, win);

    XStoreName(dpy, win, "Testing gpu");

    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST); 

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    glewInit();

    if (glDebugMessageCallbackARB != NULL) {
        glDebugMessageCallbackARB(&DebugCallbackARB, nullptr);
        if (glGetError()!=GL_NO_ERROR) printf("fuck\n");
    } else printf("thingy not supported!\n");
    
    GLuint vertexShader = loadShader("vertex_shader.glsl",GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("frag_shader.glsl",GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program,vertexShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
        
        glDeleteProgram(program);
        glDeleteShader(fragShader);
        glDeleteShader(vertexShader);

        return 1;
    }


    glValidateProgram(program);

    GLint isValid = 0;
    glGetProgramiv(program, GL_VALIDATE_STATUS, (int *)&isValid);
    if (isValid == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char infoLog[maxLength];
        glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);
        
        glDeleteProgram(program);
        glDeleteShader(fragShader);
        glDeleteShader(vertexShader);

        return 1;
    }

    glDeleteShader(fragShader);
    glDeleteShader(vertexShader);


    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    if (glGetError()) printf("error!");

    stbi_image_free(imgData);


    camera = new Camera(program);


    blocks.push_back(new Block());

    
    //printf("damnit: %d\n", XGrabPointer(dpy,win,true,0,GrabModeAsync,GrabModeAsync, win, None, CurrentTime));

    camera->pos = glm::vec3(0,0,-6);
    camera->direction = glm::vec3(0,0,1);

    tick();
    XGetWindowAttributes(dpy, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
    render();

    while(1) {
        if (XCheckWindowEvent(dpy,win,mask,&xev)) {
            switch (xev.type) {
                case KeyPress:
                    keys[xev.xkey.keycode] = true;
                    break;
                case KeyRelease:
                    keys[xev.xkey.keycode] = false;
                    switch (xev.xkey.keycode) {
                        case 9:
                            glXMakeCurrent(dpy, None, NULL);
                            glXDestroyContext(dpy, glc);
                            XDestroyWindow(dpy, win);
                            XCloseDisplay(dpy);
                            exit(0);

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
        render();
    }

    glDeleteProgram(program);

    return 0;
}