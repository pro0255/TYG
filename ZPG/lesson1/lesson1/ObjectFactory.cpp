#include "ObjectFactory.h"
#include "models/sphere.h"
#include "models/plain.h"
#include "models/suzi_smooth.h";
#include "models/suzi_flat.h"
#include "models/texture_plain.h"


float points_2[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};
//count do modelu a ten si bude vykreslovat podle bodu
void ObjectFactory::createModels()
{
	this->mp->insert({ SUZI_FLAT, new Model(suziFlat, sizeof(suziFlat)) });
	this->mp->insert({ SUZI_SMOOTH, new Model(suziSmooth, sizeof(suziSmooth)) });
	this->mp->insert({ TRIANGLE, new Model(points_2, sizeof(points_2)) });
	this->mp->insert({ SPHERE, new Model(sphere, sizeof(sphere)) });
	this->mp->insert({ PLAIN, new Model(plain, sizeof(plain)) });
	this->mp->insert({ TEXTURE_PLAIN, new Model(texture_plain, sizeof(texture_plain)) });
	printf("Factory created all models!\n");
}

Object* ObjectFactory::createObject(Model_Enum model_type)
{
	return new Object(this->mp->at(model_type));
}

Object* ObjectFactory::createObject(Model_Enum model_type, glm::vec4 color)
{
	return new Object(this->mp->at(model_type), color);
}

ObjectFactory::ObjectFactory()
{
	this->mp = new map<Model_Enum, Model*>();
	this->createModels();
}


ObjectFactory::~ObjectFactory()
{
}
