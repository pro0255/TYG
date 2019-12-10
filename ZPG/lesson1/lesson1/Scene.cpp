#include "Scene.h"
#include "models/texture_plain.h"
#include "models/sphere.h"
#include "models/suzi_smooth.h"


void Scene::init()
{
	this->objectShader = new Shader();
	this->debugShadowShader = new Shader("./shaders/DebugShadows/vertex_debugShadow.glsl", "./shaders/DebugShadows/fragment_debugShadow.glsl");
	this->camera = new Camera();
}

Scene::Scene(GLFWwindow* window)
{
	this->window = window;


	this->sceneContainer = SceneFactory::getProduct(KEY::farm);

	this->objectShader = new Shader();
	this->camera = new Camera();
	this->debugShadowShader = new Shader("./shaders/DebugShadows/vertex_debugShadow.glsl", "./shaders/DebugShadows/fragment_debugShadow.glsl");

	//tmps
	this->shadowMap = new ShadowMap();
	this->shadowMap->setup();
	//tmps


	this->objectShader->subscribeCamera(this->camera);
	this->camera->registerObserver(this->objectShader);

	//this->createPointLights();
//	this->createSpotLights();
	this->createDirectionLight();





	this->skybox = new SkyBox("./models/SkyBox/Texture/cubemap/", this->camera);
	auto* next = ObjFactory::getProduct(MODEL::house, TEXTURE::house);
	//next->scaleObject(glm::vec3(0.2));
	//next->translateObject(glm::vec3(20, 20, 20));
	this->objects.push_back(next);


	//ObjectAssimp* floor = new ObjectAssimp(new Mesh(texture_plain, sizeof(texture_plain), 8));

	//this->objects.push_back(floor);

	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		auto* lamp = ObjFactory::getProduct(MODEL::skybox, TEXTURE::pig, COLOR::blue);
		lamp->translateObject(pointLights[i]->getPosition());
		lamp->scaleObject(glm::vec3(0.2f));
		this->objects.push_back(lamp);
	}


	for (unsigned int i = 0; i < this->spotLights.size(); i++) {
		auto* lamp = ObjFactory::getProduct(MODEL::skybox, TEXTURE::none, COLOR::pink);
		lamp->translateObject(spotLights[i]->getPosition());
		lamp->scaleObject(glm::vec3(0.2f));
		this->objects.push_back(lamp);
	}





}

void Scene::draw_objects()
{
	for (int i = 0; i < this->sceneContainer->objects.size(); i++)
	{
		Renderer::draw_object(this->objectShader, this->objects.at(i)); //wtf is happening here this->skybox->objectShader
	}
	//Renderer::draw_object(this->objectShader, this->my_objects.at(0));
}

void Scene::draw_objects(Shader* new_shader)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		Renderer::draw_object(new_shader, this->objects.at(i)); //wtf is happening here this->skybox->objectShader
	}
	//Renderer::draw_object(new_shader, this->my_objects.at(0));
}



void Scene::createPointLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(10, 10, 10), ColorFactory::getProduct(COLOR::yellow)));
	this->pointLights.push_back(new PointLight(glm::vec3(10, 10, -10), ColorFactory::getProduct(COLOR::yellow)));

	objectShader->use();

	objectShader->setUniform1i("pointLightsCount", this->pointLights.size());
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		this->pointLights[i]->setShaderProperties(objectShader, i);
	}
}

void Scene::createSpotLights()
{


	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 10), ColorFactory::getProduct(COLOR::pink), ColorFactory::getProduct(COLOR::random), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, 1), glm::vec3(0, 5, 9), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(1, 0, 0), glm::vec3(0, 5, 8), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(-1, 0, -1), glm::vec3(0, 5, 7), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(-0.2, -1.0, -0.3f), glm::vec3(0, 5, 6), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 5), ColorFactory::getProduct(COLOR::green)));
	this->spotLights.push_back(new SpotLight(10, 15, glm::vec3(-1, -1, -1), glm::vec3(5, 5, -8), ColorFactory::getProduct(COLOR::white)));

	objectShader->use();

	objectShader->setUniform1i("spotLightsCount", this->pointLights.size());
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		this->spotLights[i]->setShaderProperties(objectShader, i);
	}
}

void Scene::createDirectionLight()
{
	this->flashlight = new FlashLight(12.5, this->camera);
	this->directionLight = new DirectionLight(glm::vec3(0.01, 0.01, 0.01), ColorFactory::getProduct(COLOR::white), glm::vec3(1, 1, 1), glm::vec3(-1, -1, 0));
	this->objectShader->use();
	this->directionLight->setShaderProperties(this->objectShader);
}

void Scene::renderQuad()
{
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}


Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::createObjects()
{
}

SceneContainer* Scene::getSceneContainer()
{
	return this->sceneContainer;
}

Shader* Scene::getObjectShader()
{
	return this->objectShader;
}

Shader* Scene::getDebugShadowShader()
{
	return this->debugShadowShader;
}


void Scene::draw()
{
	try {
		while (!glfwWindowShouldClose(this->window))
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


			//RENDER SHADOW MAP
			this->shadowMap->draw(this->directionLight, this->objects);



			//reset viewPort and render normal SCENE
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			int width, height;
			glfwGetFramebufferSize(this->window, &width, &height);
			glViewport(0, 0, width, height);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->objectShader->use();
			this->camera->processKeyMovement();

			//LIGHTS
			this->flashlight->draw(this->objectShader);
			this->objectShader->sendUniformVec3("viewPos", this->camera->getEye());
			//this->light->updatePosition(this->objectShader);
			this->objectShader->sendUniformMat4("lightSpaceMatrix", this->shadowMap->lightSpaceMatrix);
			//glActiveTexture(GL_TEXTURE2);
			//glBindTexture(GL_TEXTURE_2D, this->shadowMap->shadowMap);

			//this->draw_objects();	//NORMAL RENDER!
			Renderer::render(this);

			//render QUAD
			/*
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, width, height);
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->debugShadowShader->use();
			this->debugShadowShader->setUniform1f("near_plane", this->shadowMap->near_plane);
			this->debugShadowShader->setUniform1f("far_plane", this->shadowMap->far_plane);
			this->debugShadowShader->setUniform1i("shadowMap", this->shadowMap->shadowMap);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->shadowMap->shadowMap);
			this->renderQuad();
			*/
			//render QUAD

			this->skybox->draw(); //SKYBOX !
			//glClearColor(0.f, 0.0f, 0.3f, 1.0f);
			glfwPollEvents();
			glfwSwapBuffers(this->window);
		}
		glfwDestroyWindow(this->window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
	catch (const char* msg) {
		cout << msg << endl;
		glfwDestroyWindow(this->window);
		glfwTerminate();
		system("pause");
		exit(EXIT_FAILURE);
	}

}
