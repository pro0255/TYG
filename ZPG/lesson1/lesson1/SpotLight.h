#pragma once
#include "PointLight.h"
class SpotLight : public PointLight
{
public:
	virtual void setShaderProperties(Shader* shader, int index) override;
	SpotLight(float cutOff, float outerCutOff, glm::vec3 direction, glm::vec3 position, glm::vec3 ambientColor = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specularColor = glm::vec3(1), float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
	//SpotLight(glm::vec3 position, glm::vec3 ambientColor = glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3 diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3 specularColor = glm::vec3(1), float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);
	virtual glm::vec3 getPosition() override;
private:
protected:
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
};

