#include "ModelFactory.h"
#include "./models/texture_plain.h"

Mesh* ModelFactory::getProduct(MODEL type)
{
	if (this->models.size() < 1)
	{
		this->createModels();
	}

	return this->models[type];
}

void ModelFactory::createModels()
{
	this->models.insert({ MODEL::alpine, new Mesh("./models/Assimp/Farm/Alpine_chalet.obj") });
	this->models.insert({ MODEL::barn, new Mesh("./models/Assimp/Farm/barn.obj") });
	this->models.insert({ MODEL::deer, new Mesh("./models/Assimp/Farm/deer.obj") });
	this->models.insert({ MODEL::horse, new Mesh("./models/Assimp/Farm/horse.obj") });
	this->models.insert({ MODEL::log, new Mesh("./models/Assimp/Farm/log.obj") });
	this->models.insert({ MODEL::moose, new Mesh("./models/Assimp/Farm/moose.obj") });
	this->models.insert({ MODEL::pig, new Mesh("./models/Assimp/Farm/pig.obj") });
	this->models.insert({ MODEL::house, new Mesh("./models/Assimp/house.obj") });
	this->models.insert({ MODEL::skybox, new Mesh("./models/SkyBox/skybox.obj") });
	this->models.insert({ MODEL::plain_uv, new Mesh(texture_plain, sizeof(texture_plain), 6) });
	this->models.insert({ MODEL::lamp, new Mesh("./models/Assimp/Farm/lamp.obj") });
	this->models.insert({ MODEL::terrain1, new Mesh("./models/Assimp/Terrain/Terrain1.obj") });
	this->models.insert({ MODEL::tree, new Mesh("./models/Assimp/Farm/tree.obj") });
	this->models.insert({ MODEL::house2, new Mesh({"./models/Assimp/Farm/house2.obj"}) });
}


