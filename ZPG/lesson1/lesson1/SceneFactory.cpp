#include "SceneFactory.h"



IBuilder* SceneFactory::builder = nullptr;

SceneContainer* SceneFactory::getProduct(KEY key)
{
	SceneContainer* sceneContainer = nullptr;
	switch (key)
	{
	case KEY::farm:
	{
		builder = new FarmSceneBuilder();
		sceneContainer = builder->createSceneContainer();
		delete builder;
	}
	}
	return sceneContainer;
}

