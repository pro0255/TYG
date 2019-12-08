#pragma once
#include <glm/mat4x4.hpp>

class AbstractLight
{
protected:
	virtual void setShaderProperties() = 0;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
public:
	virtual void render() = 0;
};

