#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <vector>
#include "Shader.h"
#include "DirectionLight.h"
#include "ObjectAssimp.h"
class ShadowMap
{
public:
	ShadowMap();
	void setup();
	GLuint frameBuffer;
	GLuint shadowMap;
	glm::mat4 lightSpaceMatrix;
	void setShaderProperties(Shader* shader = nullptr);
	void draw(DirectionLight* sun, vector<ObjectAssimp*> objects);
	Shader* shader;
private:

};

