#pragma once
#include "Shader.h"
#include "Object.h"
#include "Scene.h"

class Scene;
class Renderer
{
public:
	Renderer();
	~Renderer();

	static void draw_object(Shader* shader, Object *object);
	static void draw_scene(Scene *scene);
};

