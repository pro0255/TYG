#include "SkyBox.h"

SkyBox::SkyBox(string prefix) : ObjectAssimp(new Mesh("./models/SkyBox/skybox.obj"), load(prefix)) { this->createShader(); }

void SkyBox::draw()
{
	glDepthMask(GL_FALSE);
	this->shader->use();
	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
	ObjectAssimp::draw(this->shader);
	glDepthMask(GL_TRUE);
}

Texture* SkyBox::load(string prefix)
{
	vector<string> faces;
	faces.push_back(prefix + "posx.jpg");
	faces.push_back(prefix + "negx.jpg");
	faces.push_back(prefix + "posy.jpg");
	faces.push_back(prefix + "negy.jpg");
	faces.push_back(prefix + "posz.jpg");
	faces.push_back(prefix + "negz.jpg");
	return new Texture(faces);
}

void SkyBox::createShader()
{
	this->shader = new Shader("./shaders/SkyBox/skybox_vertex.glsl", "./shaders/SkyBox/skybox_fragment.glsl");
}

void SkyBox::setShaderProperties()
{


}


