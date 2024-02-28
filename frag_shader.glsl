#version 330 core
  
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D block_textures;

void main()
{
    FragColor = texture(block_textures,TexCoord);
    if (FragColor == vec4(0,0,0,1))
        discard;
}
