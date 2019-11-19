#pragma once

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ObjectFactory.h"
#include "ModelEnum.h"
#include "Renderer.h"
#include <vector>
#include "Light.h"
#include "Texture.h"

class Renderer;
class Scene
{
private:




	Object* o;
	vector<Object*> my_monkeys;
	vector<Object*> my_objects;
	//Object* plain;


	GLFWwindow* window;
	ObjectFactory* factory;
	Camera* camera;
	Shader* shader;
	Light* light;

	void draw_objects();


public:
	Scene(GLFWwindow* window);

	void scaleObject();
	void createObject(glm::vec3 pos);

	Camera* getCamera();
	void createObjects();
	void draw();
	int selected_Object_Id;
};

