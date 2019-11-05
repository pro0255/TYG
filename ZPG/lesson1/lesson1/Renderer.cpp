#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::draw_object(Shader* shader, Object* object)
{
	//shader->use();
	object->bind();

	//object->translateObject(glm::vec3(1.0, 0.0, 0.0)); 
	//object->translateObject(glm::vec3(-1.0, 0.0, 0.0));
	//shader->sendUniformMat4("modelMatrix", object->getModelMatrix());
	//shader->sendUniformVec4("objectColor", object->getObjectColor());
	object->set_shader_properties(shader);
	glDrawArrays(GL_TRIANGLES, 0, object->getCountVertex());
}

void Renderer::draw_scene(Scene* scene)
{
	scene->createObject();
	scene->draw();
}
