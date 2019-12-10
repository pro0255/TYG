#pragma once

#include "Object.h"
#include "Shader.h"
#include "Camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Light.h"
#include "Mesh.h"
#include "ObjectAssimp.h"
#include "SkyBox.h"
#include "FlashLight.h"
#include "ObjFactory.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionLight.h"
#include "ShadowMap.h"
#include "Renderer.h"
#include "SceneContainer.h"
#include "SceneFactory.h"
class Renderer;
class Scene
{
private:

	GLFWwindow* window;

	Camera* camera;
	Shader* objectShader;
	Shader* debugShadowShader;
	ShadowMap* shadowMap;


	SkyBox* skybox;
	vector<ObjectAssimp*> objects;
	vector<PointLight*> pointLights;
	vector<SpotLight*> spotLights;
	DirectionLight* directionLight;

	SceneContainer* sceneContainer;



	FlashLight* flashlight;



	void draw_objects();
	void draw_objects(Shader* new_shader);


	void init();
public:



	int selectedObjectId;
	Scene(GLFWwindow* window);

	Camera* getCamera();

	SceneContainer* getSceneContainer();
	Shader* getObjectShader();
	Shader* getDebugShadowShader();


	void preDraw();
	void draw();

	void createPointLights();
	void createSpotLights();
	void createDirectionLight();
	void renderQuad();
};

