#pragma once
#include "Shader.h"
#include "soil.h"

class Texture
{
private:
	static unsigned int COUNTER;
	GLuint id;
public:

	Texture(const char* path);
	Texture();
	void set_shader_properties(Shader* shader);
};

