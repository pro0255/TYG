#pragma once
#include "Shader.h"
#include "soil.h"

class Texture
{
private:
	GLuint image;
public:

	Texture(const char* path);
	Texture();
	void createTexture();
	void bind();
	void set_shader_properties(Shader* shader);
};

