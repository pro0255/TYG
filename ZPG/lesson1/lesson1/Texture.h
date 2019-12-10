#pragma once
#include "Shader.h"
#include "soil.h"
#include <vector>


class Texture
{
private:
	static unsigned int COUNTER;
	GLuint id;
public:
	Texture(vector<string> faces);
	Texture(const char* path);
	Texture();
	void setShaderProperties(Shader* shader);
};

