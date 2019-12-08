#include "ModelFactory.h"
#include "./models/texture_plain.h"

Mesh* ModelFactory::getProduct(MODEL type)
{
	return this->models[type];
}

ModelFactory::ModelFactory()
{
	this->createModels();
}

void ModelFactory::createModels()
{
	this->models.insert({ MODEL::ALPINE, new Mesh("./models/Assimp/Farm/Alpine_chalet.obj") });
	this->models.insert({ MODEL::BARN, new Mesh("./models/Assimp/Farm/barn.obj") });
	this->models.insert({ MODEL::DEER, new Mesh("./models/Assimp/Farm/deer.obj") });
	this->models.insert({ MODEL::HORSE, new Mesh("./models/Assimp/Farm/horse.obj") });
	this->models.insert({ MODEL::LOG, new Mesh("./models/Assimp/Farm/log.obj") });
	this->models.insert({ MODEL::MOOSE, new Mesh("./models/Assimp/Farm/moose.obj") });
	this->models.insert({ MODEL::PIG, new Mesh("./models/Assimp/Farm/pig.obj") });
	this->models.insert({ MODEL::HOUSE, new Mesh("./models/Assimp/house.obj") });
	this->models.insert({ MODEL::SKYBOX, new Mesh("./models/SkyBox/skybox.obj") });
	this->models.insert({ MODEL::PLAIN_UV, new Mesh(texture_plain, sizeof(texture_plain), 6) });
}


