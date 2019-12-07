#include "Texture.h"

unsigned int Texture::COUNTER = 0;

Texture::Texture(const char* path)
{
	this->id = COUNTER++; //prideleni id texture
	glActiveTexture(GL_TEXTURE0 + this->id); //aktivace texturovaci jednotky

	GLuint textureId = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

Texture::Texture() : Texture("./textures/test.png") {}

void Texture::set_shader_properties(Shader* shader)
{
	shader->setUniform1i("textureUnitId", this->id);
}
