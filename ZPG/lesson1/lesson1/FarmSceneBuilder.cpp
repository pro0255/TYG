#include "FarmSceneBuilder.h"
#include <random>

#define DEFAULT_AMBIENT glm::vec3(0.05)

SkyBox* FarmSceneBuilder::createSkyBox()
{
	auto* skybox = new SkyBox("./models/SkyBox/Texture/cubemap/");
	return skybox;
}

DirectionLight* FarmSceneBuilder::createSun()
{
	return new DirectionLight(
		glm::vec3(0.01, 0.01, 0.01),
		ColorFactory::getProduct(COLOR::white),
		glm::vec3(1, 1, 1),
		glm::vec3(-1, -1, 0)
	);
}

vector<SpotLight*> FarmSceneBuilder::createSpotLights()
{
	vector<SpotLight*> spotLights;
	spotLights.push_back(new SpotLight(10, 20, glm::vec3(-1, -1, 0), glm::vec3(10, 10, 10), DEFAULT_AMBIENT, ColorFactory::getProduct(COLOR::random), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 15, glm::vec3(1, 1, 0), glm::vec3(2, 10, 9), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 25, glm::vec3(0.5, 1, 0), glm::vec3(-5, 10, 8), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 13, glm::vec3(-1, -1, -1), glm::vec3(0, 10, 7), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 30, glm::vec3(-1, 1.0, -0.3f), glm::vec3(0, 10, 6), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 12, glm::vec3(1, 1, -1), glm::vec3(0, 10, 5), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	spotLights.push_back(new SpotLight(10, 11, glm::vec3(-1, -1, -1), glm::vec3(5, 10, -8), DEFAULT_AMBIENT, ColorFactory::getProduct(), ColorFactory::getProduct(COLOR::white)));
	return spotLights;
}

vector<PointLight*> FarmSceneBuilder::createPointLights()
{
	vector<PointLight*> pointLights;
	pointLights.push_back(new PointLight(glm::vec3(0, 0, 0), DEFAULT_AMBIENT, ColorFactory::getProduct(COLOR::red), ColorFactory::getProduct(COLOR::white)));
	pointLights.push_back(new PointLight(glm::vec3(10, 10, -10), DEFAULT_AMBIENT, ColorFactory::getProduct(COLOR::blue), ColorFactory::getProduct(COLOR::white)));
	pointLights.push_back(new PointLight(glm::vec3(20, 8, 5), DEFAULT_AMBIENT, ColorFactory::getProduct(COLOR::pink), ColorFactory::getProduct(COLOR::white)));
	return pointLights;
}

vector<ObjectAssimp*> FarmSceneBuilder::createObjects()
{
	random_device rseed;
	mt19937 rng(rseed());
	uniform_int_distribution<int> dist(-15, 5);

	vector<ObjectAssimp*> objects;
	auto* house = ObjFactory::getProduct(MODEL::house, TEXTURE::house);
	house->scaleObject(glm::vec3(0.5f));
	objects.push_back(house);

	house = ObjFactory::getProduct(MODEL::house, TEXTURE::house);
	house->scaleObject(glm::vec3(0.3f));
	house->translateObject(glm::vec3(20, 0, -12));
	house->rotateObject(90, glm::vec3(0, 1, 0));
	objects.push_back(house);


	house = ObjFactory::getProduct(MODEL::house, TEXTURE::house);
	house->scaleObject(glm::vec3(0.5f));
	house->translateObject(glm::vec3(25, 0, 9));
	house->rotateObject(90, glm::vec3(0, 0.3, 0));
	objects.push_back(house);

	house = ObjFactory::getProduct(MODEL::barn, TEXTURE::house2);
	//house->scaleObject(glm::vec3(0.005f));
	house->translateObject(glm::vec3(50, 0, 0));
	objects.push_back(house);





	int numberOfDeers = 10;
	ObjectAssimp* deer;
	for (int i = 0; i < numberOfDeers; i++) {
		deer = ObjFactory::getProduct(MODEL::deer, TEXTURE::deer);
		deer->translateObject(glm::vec3(rand() % 15 + 3, 0, dist(rng)));
		deer->scaleObject(glm::vec3(0.005f));
		deer->rotateObject(rand() % 360, glm::vec3(0, 1, 0));
		objects.push_back(deer);
	}


	int numberOfPigs = 6;
	ObjectAssimp* pig;
	for (int i = 0; i < numberOfPigs; i++) {
		pig = ObjFactory::getProduct(MODEL::pig, TEXTURE::pig);
		pig->translateObject(glm::vec3(rand() % 15 + 3, 0, dist(rng)));
		pig->scaleObject(glm::vec3(0.005f));
		pig->rotateObject(rand() % 360, glm::vec3(0, 1, 0));
		objects.push_back(pig);
	}

	int numberOfMoose = 3;
	ObjectAssimp* moose;
	for (int i = 0; i < numberOfMoose; i++) {
		moose = ObjFactory::getProduct(MODEL::moose, TEXTURE::moose);
		moose->translateObject(glm::vec3(rand() % 15 + 3, 0, dist(rng)));
		moose->scaleObject(glm::vec3(0.005f));
		moose->rotateObject(rand() % 360, glm::vec3(0, 1, 0));
		objects.push_back(moose);
	}


	int numberOfLogs = 10;
	ObjectAssimp* log;
	for (int i = 0; i < numberOfLogs; i++) {
		log = ObjFactory::getProduct(MODEL::log, TEXTURE::moose);
		log->translateObject(glm::vec3(rand() % 15 + 3, 0, dist(rng)));
		log->scaleObject(glm::vec3(0.005f));
		log->rotateObject(rand() % 360, glm::vec3(0, 1, 0));
		objects.push_back(log);
	}


	int numberOfTrees = 10;
	ObjectAssimp* tree;
	for (int i = 0; i < numberOfTrees; i++)
	{
		tree = ObjFactory::getProduct(MODEL::tree, TEXTURE::none, COLOR::green);
		tree->translateObject(glm::vec3(rand() % 15 + 3, 0, dist(rng)));
		tree->scaleObject(glm::vec3(0.0005f));
		tree->rotateObject(rand() % 360, glm::vec3(0, 1, 0));
		objects.push_back(tree);
	}






	return objects;
}
