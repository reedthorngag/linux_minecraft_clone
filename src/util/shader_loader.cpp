#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#include "shader_loader.hpp"

unsigned int loadShader(const char* file, int type) {
    GLuint shader = glCreateShader(type);

    char buf[4096];
    char* array[1] = {buf};
    int read[1];

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

    glShaderSource(shader, 1, array,read);

    glCompileShader(shader);

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

    return shader;
};
