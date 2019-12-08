#include "DirectionLight.h"


DirectionLight::DirectionLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction) : BaseLight(ambientColor, diffuseColor, specularColor)
{
	this->direction = direction;
}

void DirectionLight::setShaderProperties(Shader* shader)
{
	string prefix = "directionLight.";
	BaseLight::setShaderProperties(shader, prefix);
	shader->sendUniformVec3((prefix + "direction").c_str(), this->direction);
}
