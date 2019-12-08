#include "SpotLight.h"

void SpotLight::setShaderProperties(Shader* shader, int index)
{
	string prefix = "spotLights[" + std::to_string(index) + "].";
	PointLight::setShaderProperties(shader, prefix);
	shader->sendUniformVec3((prefix + "direction").c_str(), this->direction);
	shader->setUniform1f((prefix + "cutOff").c_str(), this->cutOff);
	shader->setUniform1f((prefix + "outerCutOff").c_str(), this->outerCutOff);
}

SpotLight::SpotLight(float cutOff, float outerCutOff, glm::vec3 direction, glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float constant, float linear, float quadratic) : PointLight(position, ambientColor, diffuseColor, specularColor, constant, linear, quadratic)
{
	this->direction = direction;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float constant, float linear, float quadratic) : PointLight(position, ambientColor, diffuseColor, specularColor, constant, linear, quadratic)
{
	this->direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	this->cutOff = 7.5;
	this->outerCutOff = 15.5;
}
