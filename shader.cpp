#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader.hpp"

unsigned int loadShader(const char* file, int type) {
    printf("0.05\n");
    GLuint shader = glCreateShader(type);

    char buf[4096];
    char* array[1] = {buf};
    int read[1];

    printf("0.1\n");

    FILE* fd = fopen(file,"r");
    if (fd) {
        *read = fread(buf,1,4096,fd);
        if (*read==4096) {
            printf("buffer full! (%s)\n",file);
            exit(1);
        }
        fclose(fd);
    } else {
        printf("%s: failed to open shader file\n",file);
        exit(1);
    }

    printf("0.2\n");

    glShaderSource(shader, 1, array,read);

    glCompileShader(shader);

    printf("0.3\n");

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char errorLog[maxLength];
        glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog);

        printf("%s: error: %s",file, errorLog);

        glDeleteShader(shader);
        exit(1);
    }

    printf("0.4\n");

    return shader;
};
