#pragma once
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "ObjectAssimp.h"
#include "SkyBox.h"
#include "SceneContainer.h"

class IBuilder
{
private:
	virtual SkyBox* createSkyBox();
	virtual DirectionLight* createSun();
	virtual vector<SpotLight*> createSpotLights();
	virtual vector<PointLight*> createPointLights();
	virtual vector<ObjectAssimp*> createObjects();
public:
	SceneContainer* createSceneContainer();
};

