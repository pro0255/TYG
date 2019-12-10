#include "Renderer.h"


auto Renderer::drawSpotLights(vector<SpotLight*> spotLights, Shader* shader) -> void
{
	shader->use();
	shader->setUniform1i("spotLightsCount", spotLights.size());
	for (unsigned int i = 0; i < spotLights.size(); i++) {
		spotLights[i]->setShaderProperties(shader, i);
	}


}

auto Renderer::drawPointLights(vector<PointLight*> pointsLights, Shader* shader) -> void
{
	shader->use();
	shader->setUniform1i("pointLightsCount", pointsLights.size());
	for (unsigned int i = 0; i < pointsLights.size(); i++) {
		pointsLights[i]->setShaderProperties(shader, i);
	}
}

auto Renderer::drawSunLight(DirectionLight* sun, Shader* shader) -> void { sun->setShaderProperties(shader); }

void Renderer::drawLights(Scene* scene)
{
	drawSpotLights(scene->getSceneContainer()->spotLights, scene->getObjectShader());
	drawPointLights(scene->getSceneContainer()->pointLights, scene->getObjectShader());
	drawSunLight(scene->getSceneContainer()->sun, scene->getObjectShader());
	Shader::reset();
}

auto Renderer::drawObjects(Scene* scene) -> void
{
	for (auto object : scene->getSceneContainer()->objects)
	{
		glStencilFunc(GL_ALWAYS, object->id, 0xFF);
		object->draw(scene->getObjectShader());
	}
	Shader::reset();
}

auto Renderer::drawObjects(vector<ObjectAssimp*> objects, Shader* shader)
{
	for (auto object : objects)
	{
		glStencilFunc(GL_ALWAYS, object->id, 0xFF);
		object->draw(shader);
	}
	Shader::reset();
}

auto Renderer::drawSkyBox(Scene* scene) -> void
{
	scene->getSceneContainer()->skybox->draw();
	Shader::reset();
}


void Renderer::drawShadows()
{
}

auto Renderer::setViewPort(Scene* scene) -> void
{
	int width, height;
	glfwGetFramebufferSize(scene->getWindow(), &width, &height);
	glViewport(0, 0, width, height);
}

auto Renderer::setViewPort(int width, int height) -> void
{
	glViewport(0, 0, width, height);
}

void Renderer::render(Scene* scene)
{
	preRender(scene);
	scene->getFlashLight()->draw(scene->getObjectShader());
	drawObjects(scene);
	drawSkyBox(scene);
}

void Renderer::preRender(Scene* scene)
{
	if (!scene->getDrawn())
	{
		drawLights(scene);
	}
}

