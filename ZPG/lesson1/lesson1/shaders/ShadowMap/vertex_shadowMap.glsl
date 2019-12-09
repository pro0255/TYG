#version 330
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

uniform mat4 modelMatrix; //poslani matice dovnitr
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position = lightSpaceMatrix * modelMatrix * vec4(position, 1.0);
}
