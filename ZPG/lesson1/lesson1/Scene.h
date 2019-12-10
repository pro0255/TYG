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

	SceneContainer* sceneContainer;
	FlashLight* flashlight;
	bool isDrawn;
	void init();
public:
	void draw();
	void renderQuad();


	int selectedObjectId;
	Scene(GLFWwindow* window);

	Camera* getCamera();
	SceneContainer* getSceneContainer();
	Shader* getObjectShader();
	Shader* getDebugShadowShader();
	FlashLight* getFlashLight();
	GLFWwindow* getWindow();
	bool getDrawn();
};

