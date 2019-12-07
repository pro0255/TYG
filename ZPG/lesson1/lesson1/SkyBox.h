#pragma once
#include "Texture.h"
#include "ObjectAssimp.h"


class SkyBox : public ObjectAssimp
{
public:
	SkyBox(string prefix);
	void draw();
private:
	Texture* load(string prefix);
	void createShader();
	void setShaderProperties();
	Shader* shader;
};

