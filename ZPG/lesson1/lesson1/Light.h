#pragma once
#include <glm/mat4x4.hpp> // glm::mat4
#include "Shader.h"

class Light
{

private:
	float radius;
	float angle;

	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 worldPoint;

public:
	Light(glm::vec3 position, glm::vec4 color);
	glm::vec3 getLightPosition();
	glm::vec4 getLightColor();



	void updatePosition(Shader* shader);
	void set_shader_properties(Shader* shader);
};

