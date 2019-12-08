#include "FlashLight.h"

void FlashLight::draw(Shader* shader)
{
	shader->use();
	this->position = this->camera->getEye();
	this->setShaderProperties(shader);
}

FlashLight::FlashLight(float cutOff, Camera* camera) : Light(camera->getEye(), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1))
{
	this->cutOff = cutOff;
	this->camera = camera;
}

void FlashLight::update()
{
}

void FlashLight::setShaderProperties(Shader* shader)
{
	Light::setShaderProperties(shader, "flashlight.");
	shader->sendUniformVec3("flashlight.direction", this->camera->getTarget());
	shader->setUniform1f("flashlight.cutOff", glm::cos(glm::radians(this->cutOff)));
	shader->setUniform1f("flashlight.cutOff", glm::cos(glm::radians(15.0f)));
}
