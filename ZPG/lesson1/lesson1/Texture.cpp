#include "Texture.h"



Texture::Texture(const char* path)
{
	this->image = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
}

Texture::Texture() : Texture("./textures/test.png")
{

}

void Texture::createTexture()
{

}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->image);
}


void Texture::set_shader_properties(Shader* shader)
{
	shader->setUniform1i("textureUnitId", 0);
}
