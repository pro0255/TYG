#include "Renderer.h"


void Renderer::drawLights()
{
}

auto Renderer::drawObjects(Scene* scene) -> void
{
	for (auto object : scene->getSceneContainer()->objects)
	{
		glStencilFunc(GL_ALWAYS, object->id, 0xFF);
		object->draw(scene->getObjectShader());
	}
	//Shader::reset();
}

auto Renderer::drawObjects(vector<ObjectAssimp*> objects, Shader* shader)
{
	for (auto object : objects)
	{
		glStencilFunc(GL_ALWAYS, object->id, 0xFF);
		object->draw(shader);
	}
}

auto Renderer::drawSkyBox(Scene* scene) -> void
{
	scene->getSceneContainer()->skybox->draw();
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

void Renderer::render(Scene* scene)
{
	drawObjects(scene);
	drawSkyBox(scene);
}

