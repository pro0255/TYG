#include "FlashLight.h"

void FlashLight::draw(Shader* shader)
{
	shader->use();
	this->direction = camera->getTarget();
	this->position = this->camera->getEye();
	this->setShaderProperties(shader);
}

FlashLight::FlashLight(float cutOff, Camera* camera) : SpotLight(cutOff, 17.5, camera->getTarget(), camera->getEye(), glm::vec3(0.05, 0.05, 0.05), glm::vec3(1, 1, 0), glm::vec3(1, 1, 1))
{
	//this->cutOff = cutOff;
	this->camera = camera;
}

void FlashLight::update()
{
}

void FlashLight::setShaderProperties(Shader* shader)
{
	string name = "flashlight.";
	shader->sendUniformVec3((name + "direction").c_str(), this->direction);
	shader->setUniform1f((name + "cutOff").c_str(), glm::cos(glm::radians(this->cutOff)));
	shader->setUniform1f((name + "outerCutOff").c_str(), glm::cos(glm::radians(this->outerCutOff)));
	shader->sendUniformVec4((name + "position").c_str(), glm::vec4(this->position, 1));
	shader->setUniform1f((name + "constant").c_str(), this->constant);
	shader->setUniform1f((name + "linear").c_str(), this->linear);
	shader->setUniform1f((name + "quadratic").c_str(), this->quadratic);
	shader->sendUniformVec4((name + "diffuse").c_str(), glm::vec4(this->diffuseColor, 1));
	shader->sendUniformVec4((name + "specular").c_str(), glm::vec4(this->specularColor, 1));
	shader->sendUniformVec4((name + "ambient").c_str(), glm::vec4(this->ambientColor, 1));

}
