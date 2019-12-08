#include "Texture.h"

unsigned int Texture::COUNTER = 0;

Texture::Texture(vector<string> faces)
{
	this->id = COUNTER++; //prideleni id texture
	glActiveTexture(GL_TEXTURE0 + this->id); //aktivace texturovaci jednotky


	GLuint textureId = SOIL_load_OGL_cubemap(
		faces[0].c_str(),
		faces[1].c_str(),
		faces[2].c_str(),
		faces[3].c_str(),
		faces[4].c_str(),
		faces[5].c_str(),
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

Texture::Texture(const char* path)
{
	this->id = COUNTER++; //prideleni id texture
	glActiveTexture(GL_TEXTURE0 + this->id); //aktivace texturovaci jednotky

	GLuint textureId = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	//glBindTexture(GL_TEXTURE_2D, textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}


Texture::Texture() : Texture("./textures/test.png") {}

void Texture::set_shader_properties(Shader* shader)
{
	shader->setUniform1i("textureUnitId", this->id);

}
