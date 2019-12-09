#include "Scene.h"
#include "models/texture_plain.h"
#include "models/sphere.h"
#include "models/suzi_smooth.h"

//TODO:
//SHADER FUNKCE!
//zdedit z tridy a program id pak tam zustane a nebude viditelny ven
//ask old objects
//texture plain does not have light


Scene::Scene(GLFWwindow* window)
{
	this->window = window;

	this->shader = new Shader();
	this->camera = new Camera();


	//tmps
	this->shadowMap = new ShadowMap();
	this->shadowMap->setup();
	//tmps


	this->shader->subscribeCamera(this->camera);
	//this->camera->setShader(this->shader);
	this->camera->registerObserver(this->shader);


	this->createFactories();
	this->createLights(); //vytvoreni svetel
	this->drawLights(); //nasetovani svetel
	this->createPointLights();
	this->createSpotLights();
	this->createDirectionLight();


	this->skybox = new SkyBox("./models/SkyBox/Texture/cubemap/", this->camera);
	this->my_assimp_objects.push_back(this->objFac->getProduct(MODEL::HOUSE, TEXTURE::HOUSE));


	//Init of lamps to drawable vector object
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		auto* lamp = this->objFac->getProduct(MODEL::SKYBOX, TEXTURE::NONE, COLOR::BLUE);
		lamp->translateObject(pointLights[i]->getPosition());
		lamp->scaleObject(glm::vec3(0.2f));
		this->my_assimp_objects.push_back(lamp);
	}


	for (unsigned int i = 0; i < this->spotLights.size(); i++) {
		auto* lamp = this->objFac->getProduct(MODEL::SKYBOX, TEXTURE::NONE, COLOR::PINK);
		lamp->translateObject(spotLights[i]->getPosition());
		lamp->scaleObject(glm::vec3(0.2f));
		this->my_assimp_objects.push_back(lamp);
	}





}

void Scene::draw_objects()
{
	for (int i = 0; i < this->my_assimp_objects.size(); i++)
	{
		Renderer::draw_object(this->shader, this->my_assimp_objects.at(i)); //wtf is happening here this->skybox->shader
	}
}

void Scene::draw_objects(Shader* new_shader)
{
	for (int i = 0; i < this->my_assimp_objects.size(); i++)
	{
		Renderer::draw_object(new_shader, this->my_assimp_objects.at(i)); //wtf is happening here this->skybox->shader
	}
}



void Scene::createPointLights()
{
	this->pointLights.push_back(new PointLight(glm::vec3(10, 10, 10), this->colFac->getProduct(COLOR::YELLOW)));
	this->pointLights.push_back(new PointLight(glm::vec3(10, 10, -10), this->colFac->getProduct(COLOR::YELLOW)));

	shader->use();

	shader->setUniform1i("pointLightsCount", this->pointLights.size());
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		this->pointLights[i]->setShaderProperties(shader, i);
	}
}

void Scene::createSpotLights()
{
	this->flashlight = new FlashLight(12.5, this->camera);

	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 10), this->colFac->getProduct(COLOR::PINK), this->colFac->getProduct(COLOR::RANDOM), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, 1), glm::vec3(0, 5, 9), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(1, 0, 0), glm::vec3(0, 5, 8), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(-1, 0, -1), glm::vec3(0, 5, 7), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(-0.2, -1.0, -0.3f), glm::vec3(0, 5, 6), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 40, glm::vec3(0, 0, -1), glm::vec3(0, 5, 5), this->colFac->getProduct(COLOR::GREEN)));
	this->spotLights.push_back(new SpotLight(10, 15, glm::vec3(-1, -1, -1), glm::vec3(5, 5, -8), this->colFac->getProduct(COLOR::WHITE)));

	shader->use();

	shader->setUniform1i("spotLightsCount", this->pointLights.size());
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		this->spotLights[i]->setShaderProperties(shader, i);
	}
}

void Scene::createDirectionLight()
{
	this->directionLight = new DirectionLight(glm::vec3(0.05, 0.05, 0.05), this->colFac->getProduct(COLOR::WHITE), glm::vec3(1, 1, 1), glm::vec3(-0.2, -1.0f, -0.3f));

	this->shader->use();
	this->directionLight->setShaderProperties(this->shader);
}




void Scene::scaleObject()
{
	/*
	for (int i = 0; i < my_objects.size(); i++) {
		if (my_objects.at(i)->getId() == this->selected_Object_Id) {
			my_objects.at(i)->scaleObject(glm::vec3(1.5));
		}
	}
	*/
}

void Scene::createObject(glm::vec3 pos)
{
	/*
	int RANGE = 5;
	Object* created = factory->createObject(SPHERE, glm::vec4(1.0, 0.0, 0.0, 1));
	if ((camera->getEye().z + RANGE) < pos.z) {
		created->translateObject(glm::vec3(pos.x, pos.y, pos.z + 2));
	}
	else {
		printf("unproject [%f =  %f]\n", camera->getEye().z - RANGE, pos.z);
		created->translateObject(glm::vec3(pos.x, pos.y, pos.z));
	}
	my_objects.push_back(created);
	*/
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::createObjects()
{
}


void Scene::createFactories()
{
	this->colFac = new ColorFactory();
	this->objFac = new ObjFactory(this->colFac);
}

//Vytvoreni svetel
void Scene::createLights()
{




	//this->pointLights.push_back(new PointLight(glm::vec3(10, 10, 10), this->colFac->getProduct(COLOR::YELLOW)));
	//this->pointLights.push_back(new PointLight(glm::vec3(10, 10, -10), this->colFac->getProduct(COLOR::PURPLE)));
	//auto* lighttmp = new SpotLight(7.5, 15, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), this->colFac->getProduct(COLOR::BLUE));
	//this->lights2.push_back((PointLight*)lighttmp);



	//this->lights.push_back(new Light(glm::vec3(10, 10, 10), this->colFac->getProduct(COLOR::WHITE), this->colFac->getProduct(COLOR::WHITE)));
	//this->lights.push_back(new Light(glm::vec3(0, 0, 0), this->colFac->getProduct(COLOR::RED), glm::vec3(1, 0, 0)));
}


//Nastaveni svetel do sceny
void Scene::drawLights()
{
	/*
	shader->use();

	shader->setUniform1i("pointLightsCount", this->pointLights.size());
	for (unsigned int i = 0; i < this->pointLights.size(); i++) {
		this->pointLights[i]->setShaderProperties(shader, i);
	}
	*/

	/*
	shader->use();

	shader->setUniform1i("lightsCount", this->lights.size());
	for (unsigned int i = 0; i < this->lights.size(); i++) {
		this->lights[i]->setShaderProperties(shader, i);
	}
	*/
}



void Scene::draw()
{
	try {
		while (!glfwWindowShouldClose(this->window))
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			this->shadowMap->draw(this->directionLight, this->my_assimp_objects);



			//reset viewPort
			int width, height;
			glfwGetFramebufferSize(this->window, &width, &height);
			glViewport(0, 0, width, height);


			//render normal scene


			glViewport(0, 0, width, height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->shader->use();
			this->camera->processKeyMovement();





			this->flashlight->draw(this->shader);
			this->shader->sendUniformVec3("viewPos", this->camera->getEye());
			//this->light->updatePosition(this->shader);

			//this->shader->sendUniformMat4("lightSpaceMatrix", this->shadowMap->lightSpaceMatrix);
			//glActiveTexture(GL_TEXTURE2);
			//glBindTexture(GL_TEXTURE_2D, this->shadowMap->shadowMap);
			this->draw_objects();

			this->skybox->draw();
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
