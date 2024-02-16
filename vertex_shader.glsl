#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;

//out vec4 VertexColor;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //VertexColor = vec4(1.0, 1.0, 1.0, 1.0);
    // 0.015625 
    // x=1 y = 0
    TexCoord = tex;
}