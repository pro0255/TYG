#pragma once
#include "Shader.h"
#include "Object.h"
#include "Scene.h"
#include "ObjectAssimp.h"

class Scene;
class Renderer
{
private:
	static auto drawLights() -> void;
	static auto drawObjects(Scene* scene) -> void;
	static auto drawObjects(vector<ObjectAssimp*> objects, Shader* shader);
	static auto drawSkyBox(Scene* scene) -> void;
	static auto drawShadows() -> void;
public:
	static void draw_object(Shader* shader, ObjectAssimp* object);
	static void render(Scene* scene);
};

