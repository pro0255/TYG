#pragma once
#include "SceneContainer.h"
#include "IBuilder.h"
#include "FarmSceneBuilder.h"

enum class KEY
{
	farm
};


static class SceneFactory
{
public:
	static IBuilder* builder;
	static SceneContainer* getProduct(KEY key);
};

