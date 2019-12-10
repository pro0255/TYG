#include "IBuilder.h"

SkyBox* IBuilder::createSkyBox()
{
	return nullptr;
}

DirectionLight* IBuilder::createSun()
{
	return nullptr;
}

vector<SpotLight*> IBuilder::createSpotLights()
{

	return vector<SpotLight*>();
}

vector<PointLight*> IBuilder::createPointLights()
{
	return vector<PointLight*>();
}

vector<ObjectAssimp*> IBuilder::createObjects()
{
	return vector<ObjectAssimp*>();;
}

SceneContainer* IBuilder::createSceneContainer()
{
	auto* sceneContainer = new SceneContainer();
	sceneContainer->objects = this->createObjects();
	sceneContainer->pointLights = this->createPointLights();
	sceneContainer->skybox = this->createSkyBox();
	sceneContainer->spotLights = this->createSpotLights();
	sceneContainer->sun = this->createSun();
	return sceneContainer;
}
