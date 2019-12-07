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
#include "Mesh.h"
#include "ObjectAssimp.h"

class Renderer;
class Scene
{
private:
	vector<ObjectAssimp*> my_assimp_objects;
	vector<Object*> my_monkeys;
	vector<Object*> my_objects;
	//Object* plain;
	GLFWwindow* window;
	ObjectFactory* factory;
	Camera* camera;
	Shader* shader;
	Light* light;

	vector<Light*> lights;

	Mesh* my_tmp;

	void draw_objects();


public:
	Scene(GLFWwindow* window);

	void scaleObject();
	void createObject(glm::vec3 pos);

	Camera* getCamera();
	void createObjects();

	void createLights();
	void drawLights();
	void draw();
	int selected_Object_Id;
};

