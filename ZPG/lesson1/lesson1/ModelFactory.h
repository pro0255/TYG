#pragma once
#include "Mesh.h"
#include <map>
enum class MODEL {
	BARN,
	DEER,
	HORSE,
	LOG,
	MOOSE,
	PIG,
	ALPINE,
	CUBE,
	HOUSE,
	SKYBOX,
	PLAIN_UV,
};


class ModelFactory
{
public:
	Mesh* getProduct(MODEL type);
	ModelFactory();
private:
	void createModels();
	map<MODEL, Mesh*> models;
};

