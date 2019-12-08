#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include "Shader.h"
class BaseLight
{
protected:
	virtual void setShaderProperties(Shader* shader, string name);

	BaseLight(glm::vec3 ambientColor = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specularColor = glm::vec3(1));
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
public:
	virtual void render(Shader* shader) = 0;
	virtual void setShaderProperties(Shader* shader) = 0;
};

