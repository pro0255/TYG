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
	//object->translateObject(glm::vec3(1.0, 0.0, 0.0)); 
	//object->translateObject(glm::vec3(-1.0, 0.0, 0.0));
	//shader->sendUniformMat4("modelMatrix", object->getModelMatrix());
	//shader->sendUniformVec4("objectColor", object->getObjectColor());
	glStencilFunc(GL_ALWAYS, object->getId(), 0xFF);
	object->rotateObject(0.01, glm::vec3(1.0, 1.0, 1.0));
	//object->rotateObject(0.1, glm::vec3(1, 0, 1));
	glDrawArrays(GL_TRIANGLES, 0, object->getCountVertex());
}


void Renderer::draw_object(Shader* shader, ObjectAssimp* object) {
	shader->use();
	glStencilFunc(GL_ALWAYS, object->id, 0xFF);
	object->rotateObject(0.1, glm::vec3(1, 0, 0));
	object->draw(shader);
}

void Renderer::draw_scene(Scene* scene)
{
	scene->createObjects();
	scene->draw();
}
