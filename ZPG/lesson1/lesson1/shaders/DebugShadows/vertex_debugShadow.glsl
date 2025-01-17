#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    gl_Position = vec4(position, 1.0);
}