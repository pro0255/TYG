#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include  "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
class ObjectAssimp
{
private:
	static int GENERATE_ID;
	Mesh* mesh;
	glm::mat4 modelMatrix;
	glm::vec4 color;
public:
	int id;
	ObjectAssimp(Mesh* mesh);
	ObjectAssimp(Mesh* mesh, glm::vec4 color);
	void rotateObject(float angle, glm::vec3 vector);
	void translateObject(glm::vec3 vector);
	void scaleObject(glm::vec3 vector);
	void resetObject();
	void set_shader_properties(Shader* shader);
	void draw(Shader* shader);
};

