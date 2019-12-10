#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::draw_object(Shader* shader, Object* object)
{
	object->set_shader_properties(shader);
	//shader->use();
	object->bind();
	glStencilFunc(GL_ALWAYS, object->getId(), 0xFF);
	glDrawArrays(GL_TRIANGLES, 0, object->getCountVertex());
}


void Renderer::draw_object(Shader* shader, ObjectAssimp* object) {
	shader->use();
	glStencilFunc(GL_ALWAYS, object->id, 0xFF);
	//object->rotateObject(0.1, glm::vec3(1, 0, 0));
	object->draw(shader);
}

void Renderer::draw_scene(Scene* scene)
{
	scene->createObjects();
	scene->draw();
}
