#pragma once
#include "Mesh.h"
#include <map>
enum class MODEL {
	barn,
	deer,
	horse,
	log,
	moose,
	pig,
	alpine,
	cube,
	house,
	skybox,
	plain_uv,
	lamp,
	terrain1
};


class ModelFactory
{
public:
	Mesh* getProduct(MODEL type);
private:
	void createModels();
	map<MODEL, Mesh*> models;
};

