#pragma once
#include "IBuilder.h"
#include "ColorFactory.h"
#include "ObjFactory.h"
class FarmSceneBuilder : public IBuilder
{
private:
	SkyBox* createSkyBox() override;
	DirectionLight* createSun() override;
	vector<SpotLight*> createSpotLights() override;
	vector<PointLight*> createPointLights() override;
	vector<ObjectAssimp*> createObjects() override;
};

