#pragma once
#include "BaseLight.h"
#include "ObjectAssimp.h"
class PointLight : BaseLight
{
public:
	virtual void render(Shader* shader) override;
	virtual void setShaderProperties(Shader* shader) override;
	virtual void setShaderProperties(Shader* shader, string name) override;
	virtual void setShaderProperties(Shader* shader, int index);
	virtual glm::vec3 getPosition();
	PointLight(glm::vec3 position, glm::vec3 ambientColor = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specularColor = glm::vec3(1), float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
private:
protected:
	glm::vec3 position;
	ObjectAssimp* object;
	float constant;
	float linear;
	float quadratic;
};

