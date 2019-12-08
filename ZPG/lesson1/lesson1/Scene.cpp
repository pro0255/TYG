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
	this->shader->subscribeCamera(this->camera);
	//this->camera->setShader(this->shader);
	this->camera->registerObserver(this->shader);


	this->createFactories();
	this->createLights(); //vytvoreni svetel
	this->drawLights(); //nasetovani svetel

	//this->my_assimp_objects.push_back(new ObjectAssimp(new Mesh(texture_plain, sizeof(texture_plain), 6)));
	//this->my_assimp_objects.at(0)->translateObject(glm::vec3(20, 0, 0));

	Texture* house_texture = new Texture("./textures/house.png");
	Texture* monkey = new Texture("./textures/monkey.png");
	Texture* barn = new Texture("./textures/barn.png");
	Texture* log_texture = new Texture("./textures/log.png");

	Mesh* house = new Mesh("./models/Assimp/house.obj");
	Mesh* cube = new Mesh("./models/Assimp/cube.obj");
	Mesh* skybox_model = new Mesh("./models/SkyBox/skybox.obj");
	Mesh* log_model = new Mesh("./models/Assimp/Farm/log.obj");
	Mesh* pig_model = new Mesh("./models/Assimp/Farm/pig.obj");
	Mesh* tmp = new Mesh("./models/Assimp/Farm/Alpine_chalet.obj");

	this->skybox = new SkyBox("./models/SkyBox/Texture/cubemap/", this->camera);
	this->skybox->translateObject(this->camera->getEye());
	//this->my_assimp_objects.push_back(new ObjectAssimp(house, house_texture));
	//this->my_assimp_objects.push_back(new ObjectAssimp(house, monkey));
//	this->my_assimp_objects.at(1)->translateObject(glm::vec3(20.0, 0, 0));
	//this->my_assimp_objects.push_back(new ObjectAssimp(house, monkey));


	this->my_assimp_objects.push_back(this->objFac->getProduct(MODEL::HOUSE, TEXTURE::MONKEY));



	this->my_assimp_objects.at(0)->rotateObject(5, glm::vec3(1, 0, 1));


	this->my_assimp_objects.push_back(new ObjectAssimp(house, monkey));
	this->my_assimp_objects.at(1)->rotateObject(5, glm::vec3(0, 1, 1));
	this->my_assimp_objects.at(1)->translateObject(glm::vec3(0, 0, 5));
	//this->my_assimp_objects.push_back(new ObjectAssimp(house, monkey));
	//this->my_assimp_objects.at(0)->scaleObject(glm::vec3(0.2));
	//auto tmp = new ObjectAssimp(skybox_model, this->skybox->cubemap);
	//tmp->translateObject(this->camera->getEye());
	//this->my_assimp_objects.push_back(tmp);



	//Init of lamps to drawable vector object
	for (unsigned int i = 0; i < this->lights.size(); i++) {
		auto* lamp = new ObjectAssimp(skybox_model, glm::vec4(1, 1, 1, 1));
		lamp->translateObject(lights[i]->getLightPosition());
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

	//glUseProgram(0);
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
	this->flashlight = new FlashLight(12.5, this->camera);

	this->lights.push_back(new Light(glm::vec3(10, 10, 10), this->colFac->getProduct(COLOR::WHITE), this->colFac->getProduct(COLOR::WHITE)));
	this->lights.push_back(new Light(glm::vec3(0, 0, 0), this->colFac->getProduct(COLOR::RED), glm::vec3(1, 0, 0)));
}


//Nastaveni svetel do sceny
void Scene::drawLights()
{
	shader->use();

	shader->setUniform1i("lightsCount", this->lights.size());
	for (unsigned int i = 0; i < this->lights.size(); i++) {
		this->lights[i]->setShaderProperties(shader, i);
	}
}



void Scene::draw()
{
	try {
		while (!glfwWindowShouldClose(this->window))
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);




			this->shader->use();
			this->camera->processKeyMovement();
			this->flashlight->draw(this->shader);
			this->shader->sendUniformVec3("viewPos", this->camera->getEye());
			//this->light->updatePosition(this->shader);
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
