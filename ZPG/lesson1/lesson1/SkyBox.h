#pragma once
#include "Texture.h"
#include "ObjectAssimp.h"
#include "Camera.h"

class SkyBox : public ObjectAssimp
{
public:
	SkyBox(string prefix, Camera* camera);
	SkyBox(string prefix);
	void draw();
	Shader* shader;
	Camera* camera;
	void setCameraPosition(Camera* camera);
private:
	Texture* load(string prefix);
	void createShader(Camera* camera);
	void setShaderProperties();
};

