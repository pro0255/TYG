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
	static auto drawObjects() -> void;
	static auto drawSkyBox() -> void;
	static auto drawShadows() -> void;
public:
	static void draw_object(Shader* shader, ObjectAssimp* object);
	static void draw(Scene* scene);
};

