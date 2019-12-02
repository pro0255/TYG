#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

//object vao my pozadame objekt aby se nastavil

class Model
{
private:
	GLuint VAO;
	GLuint VBO;
	const float* points;
	int size;
	int count_vertex;

public:
	void createVBO();
	void createVAO();
	GLuint getVAO();
	int getCountVertex();
	Model(const float* points, int size);
	~Model();
};

