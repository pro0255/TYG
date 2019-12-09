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
#include "SkyBox.h"
#include "FlashLight.h"
#include "ColorFactory.h"
#include "ModelFactory.h"
#include "ObjFactory.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionLight.h"
#include "ShadowMap.h"

class Renderer;
class Scene
{
private:
	vector<ObjectAssimp*> my_assimp_objects;
	vector<Object*> my_monkeys;
	vector<Object*> my_objects;
	//Object* plain;
	GLFWwindow* window;

	Camera* camera;
	Shader* shader;
	Light* light;


	ShadowMap* shadowMap;
	SkyBox* skybox;
	vector<PointLight*> pointLights;
	vector<SpotLight*> spotLights;
	DirectionLight* directionLight;
	FlashLight* flashlight;

	Mesh* my_tmp;

	void draw_objects();
	void draw_objects(Shader* new_shader);



	ObjFactory* objFac;
	ColorFactory* colFac;

public:
	Scene(GLFWwindow* window);

	void scaleObject();
	void createObject(glm::vec3 pos);

	Camera* getCamera();
	void createObjects();



	void createFactories();
	void createLights();
	void drawLights();
	void draw();
	int selected_Object_Id;


	void createPointLights();
	void createSpotLights();
	void createDirectionLight();
};

