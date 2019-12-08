#include "BaseLight.h"
#pragma once
class DirectionLight : BaseLight
{
public:
	virtual void render(Shader* shader);
	virtual void setShaderProperties(Shader* shader) override;
	DirectionLight(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f));
protected:
	glm::vec3 direction;
private:
};

