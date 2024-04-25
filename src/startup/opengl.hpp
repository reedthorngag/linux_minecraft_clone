#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "window.hpp"

GLuint program;

void debugCallback(GLenum source,
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

int imgWidth, imgHeight, nrChannels;
unsigned char *imgData = stbi_load("textures/blocks.png", &imgWidth, &imgHeight, &nrChannels, 0);

void setupOpenGL() {
    glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
    glXMakeCurrent(dpy, win, glc);

    glEnable(GL_DEPTH_TEST); 

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;

    GLenum err = glewInit();
    if (err != GLEW_OK) {
	printf("error: %s",glewGetErrorString(err));
	exit(1);
    } 

    printf("GL Version: %s\n",glGetString(GL_VERSION));

    if (!GLEW_VERSION_2_1) exit(1);

    if (glDebugMessageCallbackARB != NULL) {
        glDebugMessageCallbackARB(&debugCallback, nullptr);
        if (glGetError()!=GL_NO_ERROR) printf("fuck\n");
    } else printf("thingy not supported!\n");
    
    GLuint vertexShader = loadShader("src/shaders/vertex_shader.glsl",GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("src/shaders/frag_shader.glsl",GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
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

        exit(1);
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

        exit(1);
    }

    glDeleteShader(fragShader);
    glDeleteShader(vertexShader);


    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imgData);

    XGetWindowAttributes(dpy, win, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);
}
