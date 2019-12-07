#version 330
layout(location=0) in vec3 position;

uniform mat4 modelMatrix; //poslani matice dovnitr
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoords;

void main () {
	TexCoords = position;
	gl_Position = (projectionMatrix*viewMatrix*modelMatrix) * vec4(position, 1.0);
};