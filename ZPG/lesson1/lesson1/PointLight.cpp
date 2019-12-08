#include "PointLight.h"

void PointLight::render(Shader* shader)
{
}

void PointLight::setShaderProperties(Shader* shader)
{
	//BaseLight::setShaderProperties(shader);

}

void PointLight::setShaderProperties(Shader* shader, string name)
{
	BaseLight::setShaderProperties(shader, name);
	shader->sendUniformVec4((name + "position").c_str(), glm::vec4(this->position, 1));
	shader->setUniform1f((name + "constant").c_str(), this->constant);
	shader->setUniform1f((name + "linear").c_str(), this->linear);
	shader->setUniform1f((name + "quadratic").c_str(), this->quadratic);
}

void PointLight::setShaderProperties(Shader* shader, int index)
{
	//lights before
	string prefix = "pointLights[" + std::to_string(index) + "].";
	this->setShaderProperties(shader, prefix);
}

glm::vec3 PointLight::getPosition()
{
	return this->position;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, float constant, float linear, float quadratic) : BaseLight(ambientColor, diffuseColor, specularColor)
{
	this->object = nullptr;
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}
