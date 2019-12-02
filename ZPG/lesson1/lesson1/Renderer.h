#pragma once
#include "Shader.h"
#include "Object.h"
#include "Scene.h"
#include "ObjectAssimp.h"

class Scene;
class Renderer
{
public:
	Renderer();
	~Renderer();

	static void draw_object(Shader* shader, Object* object);
	static void draw_object(Shader* shader, ObjectAssimp* object);
	static void draw_scene(Scene* scene);
};

