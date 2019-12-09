#include "ShadowMap.h"


#define SHADOW_WIDTH 1024;
#define SHADOW_HEIGHT 1024;


ShadowMap::ShadowMap()
{
	this->shader = new Shader("./shaders/ShadowMap/vertex_shadowMap.glsl", "./shaders/ShadowMap/fragment_shadowMap.glsl");
}

void ShadowMap::setup()
{

	this->frameBuffer = 0;
	if (this->frameBuffer == 0) glGenFramebuffers(1, &this->frameBuffer);
	if (this->shadowMap == 0) glDeleteTextures(1, &this->shadowMap);

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &this->shadowMap);
	glBindTexture(GL_TEXTURE_2D, this->shadowMap);

	//TODO: edit height width
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glBindFramebuffer(GL_FRAMEBUFFER, this->frameBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR: Something's wrong with framebuffer.\n");
	}
}

void ShadowMap::setShaderProperties(Shader* out_shader)
{
	if (out_shader == nullptr) {
		this->shader->use();
	}
	else {
		out_shader->use();
	}
	this->shader->sendUniformMat4("lightSpaceMatrix", this->lightSpaceMatrix);
}

void ShadowMap::draw(DirectionLight* sun, vector<ObjectAssimp*> objects)
{

	//render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 lightProjection, lightView;
	float near_plane = 0.1f, far_plane = 100.0f;

	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(sun->direction, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	this->lightSpaceMatrix = lightProjection * lightView;

	//render scene from lights point of view
	this->setShaderProperties();

	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowMap);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (auto obj : objects) {
		obj->drawShadow(this->shader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
