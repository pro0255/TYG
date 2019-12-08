#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include "Shader.h"

class Light
{

private:
	float radius;
	float angle;


	glm::vec4 color;
	glm::vec3 worldPoint;


	//Fragment struct properties;

	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 ambientColor;

protected:
	void setShaderProperties(Shader* shader, string name);
	glm::vec3 position;

public:
	Light(glm::vec3 position, glm::vec4 color);
	Light(glm::vec3 position, glm::vec3 diffuseColor, glm::vec3 specularColor);
	Light(glm::vec3 position, glm::vec3 colorAll);
	glm::vec3 getLightPosition();
	glm::vec4 getLightColor();

	void updatePosition(Shader* shader);
	void set_shader_properties(Shader* shader);
	void setShaderProperties(Shader* shader, int index);
};

