#pragma once
#include "Light.h"
#include "SpotLight.h"
#include "Camera.h"
class FlashLight : public SpotLight
{
public:
	void draw(Shader* shader);
	FlashLight(float cutOff, Camera* camera);
private:
	//float cutOff;
	Camera* camera;
	void update();
	void setShaderProperties(Shader* shader);
};

