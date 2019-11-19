#include "Light.h"

Light::Light(glm::vec3 position, glm::vec4 color)
{
	this->position = position;
	this->color = color;
	this->angle = 0;
	this->radius = 5;
	this->worldPoint = glm::vec3(0.0, 0.0, 0.0);
}

glm::vec3 Light::getLightPosition()
{
	return this->position;
}

glm::vec4 Light::getLightColor()
{
	return this->color;
}

void Light::updatePosition(Shader* shader)
{
	this->angle += 0.1;
	if (this->angle == 360) {
		this->angle = 0;
	}
	float x = this->worldPoint.x + this->radius * cos(angle);
	float y = this->worldPoint.y + this->radius * sin(angle);
	float z = this->worldPoint.z + this->radius * sin(angle);
	this->position = glm::vec3(0, 0, 0);
	shader->sendUniformVec3("lightPosition", this->position);
}

void Light::set_shader_properties(Shader* shader)
{
	shader->sendUniformVec3("lightPosition", this->position);
	shader->sendUniformVec4("lightColor", this->color);
}
