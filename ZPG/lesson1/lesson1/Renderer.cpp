#include "Renderer.h"


void Renderer::drawLights()
{
}

void Renderer::drawObjects()
{
}

void Renderer::drawSkyBox()
{
}

void Renderer::drawShadows()
{
}


void Renderer::draw_object(Shader* shader, ObjectAssimp* object) {
	shader->use();
	glStencilFunc(GL_ALWAYS, object->id, 0xFF);
	//object->rotateObject(0.1, glm::vec3(1, 0, 0));
	object->draw(shader);
}

void Renderer::draw(Scene* scene)
{
}
