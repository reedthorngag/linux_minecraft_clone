#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "block.hpp"
#include "camera.hpp"

int width = 800;
int height = 600;

int halfWidth = width/2;
int halfHeight = height/2;

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

void render() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

    swa.colormap = cmap;
    swa.event_mask = ExposureMask
                    | KeyPressMask
                    | KeyReleaseMask
                    | ButtonReleaseMask
                    | PointerMotionMask;
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

    camera = new Camera(program);


    blocks.push_back(new Block());


    
    printf("damnit: %d\n", XGrabPointer(dpy,win,false,0,GrabModeAsync,GrabModeAsync, None, None, 0));

    while(1) {
 	    XNextEvent(dpy, &xev);
        
        switch (xev.type) {
            case Expose:
                XGetWindowAttributes(dpy, win, &gwa);
                glViewport(0, 0, gwa.width, gwa.height);
        	    render();
                break;
            
            case KeyPress:
                if (xev.xkey.keycode == 9) {
                    glXMakeCurrent(dpy, None, NULL);
                    glXDestroyContext(dpy, glc);
                    XDestroyWindow(dpy, win);
                    XCloseDisplay(dpy);
                    exit(0);
                } else {
                    printf("keycode: %d\n",xev.xkey.keycode);
                }
                break;
            case MotionNotify:
                if (xev.xmotion.x==halfWidth && xev.xmotion.y==halfHeight) break;
                camera->rotate(xev.xmotion.x-halfWidth,xev.xmotion.y-halfHeight);
                //XWarpPointer(dpy,win,0, 0, width, height, halfWidth, halfHeight,0);
                printf("pointer: x %d, y %d\n",xev.xmotion.x-halfWidth,xev.xmotion.y-halfHeight);
                break;
        }
    }

    glDeleteProgram(program);

    return 0;
}
