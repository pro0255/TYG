#pragma once
#include "Shader.h"
#include "Object.h"
#include "Scene.h"
#include "ObjectAssimp.h"

class Scene;
class Renderer
{
private:
	static auto drawSpotLights(vector<SpotLight*> spotLights, Shader* shader) -> void;
	static auto drawPointLights(vector<PointLight*> pointsLights, Shader* shader) -> void;
	static auto drawSunLight(DirectionLight* sun, Shader* shader) -> void;
	static auto drawLights(Scene* scene) -> void;
	static auto drawObjects(Scene* scene) -> void;
	static auto drawObjects(vector<ObjectAssimp*> objects, Shader* shader);
	static auto drawSkyBox(Scene* scene) -> void;
	static auto drawShadows() -> void;
	static auto setViewPort(Scene* scene) -> void;
	static auto setViewPort(int width, int height) -> void;
public:
	static void render(Scene* scene);
	static void preRender(Scene* scene);
};

