#include "FarmSceneBuilder.h"

SkyBox* FarmSceneBuilder::createSkyBox()
{
	auto* skybox = new SkyBox("./models/SkyBox/Texture/cubemap/");
	return skybox;
}

DirectionLight* FarmSceneBuilder::createSun()
{
	return new DirectionLight(
		glm::vec3(0.01, 0.01, 0.01),
		ColorFactory::getProduct(COLOR::red),
		glm::vec3(1, 1, 1),
		glm::vec3(-1, -1, 0)
	);
}

vector<SpotLight*> FarmSceneBuilder::createSpotLights()
{
	vector<SpotLight*> spotLights;
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 10), ColorFactory::getProduct(COLOR::pink), ColorFactory::getProduct(COLOR::random), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, 1), glm::vec3(0, 5, 9), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(1, 0, 0), glm::vec3(0, 5, 8), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(-1, 0, -1), glm::vec3(0, 5, 7), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(-0.2, -1.0, -0.3f), glm::vec3(0, 5, 6), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 5), ColorFactory::getProduct(COLOR::green)));
	spotLights.push_back(new SpotLight(10, 15, glm::vec3(-1, -1, -1), glm::vec3(5, 5, -8), ColorFactory::getProduct(COLOR::white)));
	return spotLights;
}

vector<PointLight*> FarmSceneBuilder::createPointLights()
{
	vector<PointLight*> pointLights;
	pointLights.push_back(new PointLight(glm::vec3(0, 0, 0), ColorFactory::getProduct(COLOR::blue), ColorFactory::getProduct(COLOR::red)));
	pointLights.push_back(new PointLight(glm::vec3(10, 10, -10), ColorFactory::getProduct(COLOR::blue), ColorFactory::getProduct(COLOR::random)));
	return pointLights;
}

vector<ObjectAssimp*> FarmSceneBuilder::createObjects()
{
	vector<ObjectAssimp*> objects;
	auto* house = ObjFactory::getProduct(MODEL::house, TEXTURE::house);
	//next->scaleObject(glm::vec3(0.2));
	//next->translateObject(glm::vec3(20, 20, 20));
	objects.push_back(house);

	return objects;
}
