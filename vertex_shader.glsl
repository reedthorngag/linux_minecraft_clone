#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tex;

//out vec4 VertexColor;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

uniform uint tex_offset;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    TexCoord = vec2((tex_offset+tex.x)*0.006836,tex.y*0.0136);
}