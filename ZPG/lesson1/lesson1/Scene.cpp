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
	this->factory = new ObjectFactory();
	this->shader = new Shader();
	this->camera = new Camera();
	this->shader->subscribeCamera(this->camera);
	this->camera->setShader(this->shader);
	//this->light = new Light(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec4(1.0, 1.0, 1.0, 1.0));
	//this->light->set_shader_properties(this->shader);


	this->createLights(); //vytvoreni svetel
	this->drawLights(); //nasetovani svetel

	//this->my_assimp_objects.push_back(new ObjectAssimp(new Mesh(texture_plain, sizeof(texture_plain), 6)));
	//this->my_assimp_objects.at(0)->translateObject(glm::vec3(20, 0, 0));

	Texture* house_texture = new Texture("./textures/test.png");
	Texture* monkey = new Texture("./textures/monkey.png");

	Mesh* house = new Mesh("./models/Assimp/test.obj");
	Mesh* cube = new Mesh("./models/Assimp/cube.obj");
	Mesh* skybox_model = new Mesh("./models/SkyBox/skybox.obj");

	this->skybox = new SkyBox("./models/SkyBox/Texture/cubemap/");
	this->skybox->translateObject(this->camera->getEye());
	this->my_assimp_objects.push_back(new ObjectAssimp(house, house_texture));
	this->my_assimp_objects.push_back(new ObjectAssimp(house, monkey));
	//this->my_assimp_objects.at(1)->translateObject(glm::vec3(20.0, 0, 0));
	//this->my_assimp_objects.push_back(this->skybox);

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







void Scene::scaleObject()
{
	for (int i = 0; i < my_objects.size(); i++) {
		if (my_objects.at(i)->getId() == this->selected_Object_Id) {
			my_objects.at(i)->scaleObject(glm::vec3(1.5));
		}
	}
}

void Scene::createObject(glm::vec3 pos)
{
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
}

Camera* Scene::getCamera()
{
	return this->camera;
}

void Scene::createObjects()
{
}


//Vytvoreni svetel
void Scene::createLights()
{
	this->lights.push_back(new Light(glm::vec3(10, 10, 10), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1)));
	this->lights.push_back(new Light(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(1, 0, 0)));
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

void Scene::draw_objects()
{

	this->skybox->draw();
	for (int i = 0; i < this->my_assimp_objects.size(); i++)
	{
		Renderer::draw_object(this->shader, this->my_assimp_objects.at(i));
	}
}


void Scene::draw()
{
	try {
		glm::mat4 M = glm::mat4(1.0f);
		//float rotation = 0.1f;
		while (!glfwWindowShouldClose(this->window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			this->camera->processKeyMovement();
			this->shader->sendUniformVec3("viewPos", this->camera->getEye());
			//this->light->updatePosition(this->shader);
			this->draw_objects();

			glClearColor(0.f, 0.0f, 0.3f, 1.0f);
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
