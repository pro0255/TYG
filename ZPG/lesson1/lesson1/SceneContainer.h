#pragma once
#include <vector>
#include <string>
#include "ObjectAssimp.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "SkyBox.h"


using namespace std;
class SceneContainer
{
public:
	vector<ObjectAssimp*> objects;
	vector <PointLight*> pointLights;
	vector<SpotLight*> spotLights;
	DirectionLight* sun;
	SkyBox* skybox;
};

