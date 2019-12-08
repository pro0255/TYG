#include "BaseLight.h"

void BaseLight::setShaderProperties(Shader* shader, string name)
{
	shader->use();
	shader->sendUniformVec4((name + "diffuse").c_str(), glm::vec4(this->diffuseColor, 1));
	shader->sendUniformVec4((name + "specular").c_str(), glm::vec4(this->specularColor, 1));
	shader->sendUniformVec4((name + "ambient").c_str(), glm::vec4(this->ambientColor, 1));
}

BaseLight::BaseLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor)
{
	this->ambientColor = ambientColor;
	this->diffuseColor = diffuseColor;
	this->specularColor = specularColor;
}
