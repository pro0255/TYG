#include "SkyBox.h"

SkyBox::SkyBox(string prefix, Camera* camera) : ObjectAssimp(new Mesh("./models/SkyBox/skybox.obj"), load(prefix)) { this->createShader(camera); this->camera = camera; }


void SkyBox::draw()
{
	//glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);
	this->shader->use();
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	this->setShaderProperties();
	this->mesh->draw(this->shader);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
	//ObjectAssimp::draw(this->shader);
	//glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glUseProgram(0);
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

void SkyBox::createShader(Camera* camera)
{
	this->shader = new Shader("./shaders/SkyBox/skybox_vertex.glsl", "./shaders/SkyBox/skybox_fragment.glsl");
	this->shader->subscribeCamera(camera);
}

void SkyBox::setShaderProperties()
{
	this->shader->sendUniformMat4("modelMatrix", glm::mat4(1));
	this->shader->sendUniformMat4("viewMatrix", glm::mat4(glm::mat3(this->camera->getCamera()))); //maybe delete
	this->shader->sendUniformMat4("projectionMatrix", this->camera->getProjectionMatrix());
	this->shader->sendUniformVec4("objectColor", glm::vec4(1));
	this->shader->setUniform1i("hasObjectTexture", this->texture != nullptr); //1-false 0-true
	if (texture != nullptr) {
		this->texture->set_shader_properties(shader);
	}
}



