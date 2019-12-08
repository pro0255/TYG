#include "FlashLight.h"

void FlashLight::draw(Shader* shader)
{
	shader->use();
	this->position = this->camera->getEye();
	this->setShaderProperties(shader);
}

FlashLight::FlashLight(float cutOff, Camera* camera) : Light(camera->getEye(), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1))
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
}
