#include "Scene.h"

//TODO:
//SHADER FUNKCE!
//zdedit z tridy a program id pak tam zustane a nebude viditelny ven
Scene::Scene(GLFWwindow* window)
{
	this->window = window;
	this->factory = new ObjectFactory();
	this->shader = new Shader();
	this->camera = new Camera();
	this->shader->subscribeCamera(this->camera);
	this->camera->setShader(this->shader);
	this->shader->use();
	this->light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0, 1.0, 1.0, 1.0));
	this->light->set_shader_properties(this->shader);
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
	//this->o = factory->createObject(TRIANGLE);

	//this->o = factory->createObject(SUZI_FLAT);


	/*
	this->plain = this->factory->createObject(PLAIN, glm::vec4(0.0, 1.0, 0.0, 1.0));
	this->plain->translateObject(glm::vec3(0.0, -20, 0));
	this->plain->scaleObject(glm::vec3(100));
	*/


	/*
	this->my_monkeys.push_back(this->factory->createObject(SUZI_FLAT, glm::vec4(0.0, 0.0, 1.0, 1.0)));
	this->my_monkeys.at(0)->translateObject(glm::vec3(5.0, 0.0, -1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_FLAT, glm::vec4(0.0, 1.0, 0.0, 1.0)));
	this->my_monkeys.at(1)->translateObject(glm::vec3(-5.0, 0.0, -1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_FLAT, glm::vec4(1.0, 0.0, 0.0, 1.0)));
	this->my_monkeys.at(2)->translateObject(glm::vec3(0.0, 5.0, -1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_FLAT));
	this->my_monkeys.at(3)->translateObject(glm::vec3(0.0, -5.0f, -1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_SMOOTH, glm::vec4(0.0, 1.0, 0.0, 1.0)));
	this->my_monkeys.at(4)->translateObject(glm::vec3(3.0, 3.0, 1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_SMOOTH, glm::vec4(1.0, 0.0, 0.0, 1.0)));
	this->my_monkeys.at(5)->translateObject(glm::vec3(3.0, -3.0, 1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_SMOOTH, glm::vec4(0.0, 0.0, 1.0, 1.0)));
	this->my_monkeys.at(6)->translateObject(glm::vec3(-3.0, 3.0, 1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_SMOOTH));
	this->my_monkeys.at(7)->translateObject(glm::vec3(-3.0, -3.0, 1.0));
	this->my_monkeys.push_back(this->factory->createObject(SUZI_SMOOTH, glm::vec4(1.0, 0.0, 0.0, 0.0)));
	this->my_monkeys.at(8)->translateObject(glm::vec3(1.0, 1.0, -10));
	this->my_monkeys.at(8)->scaleObject(glm::vec3(10.0f));
	*/


	//this->o->translateObject(glm::vec3(5.0f, 0.0f, 0.0f));
	this->my_objects.push_back(this->factory->createObject(TEXTURE_PLAIN));
	this->my_objects.at(0)->translateObject(glm::vec3(2.0f, 0.0f, 0.0f));
	this->my_objects.push_back(this->factory->createObject(TEXTURE_PLAIN));
	this->my_objects.at(1)->translateObject(glm::vec3(-2.0f, 0.0f, 0.0f));
	this->my_objects.push_back(this->factory->createObject(TEXTURE_PLAIN));
	this->my_objects.at(2)->translateObject(glm::vec3(0.0f, 2.0f, 0.0f));
	this->my_objects.push_back(this->factory->createObject(TEXTURE_PLAIN));
	this->my_objects.at(3)->translateObject(glm::vec3(0.0f, -2.0f, 0.0f));
	this->my_objects.push_back(this->factory->createObject(SPHERE));
	this->my_objects.at(4)->translateObject(glm::vec3(5.0f, -2.0f, 0.0f));

}

void Scene::draw_objects()
{
	//Renderer::draw_object(this->shader, this->plain);

	for (int i = 0; i < this->my_objects.size(); i++) {
		Renderer::draw_object(this->shader, this->my_objects.at(i));
	}

	for (int i = 0; i < this->my_monkeys.size(); i++) {
		Renderer::draw_object(this->shader, this->my_monkeys.at(i));
	}
}


void Scene::draw()
{
	try {
		glm::mat4 M = glm::mat4(1.0f);
		//float rotation = 0.1f;
		while (!glfwWindowShouldClose(this->window))
		{
			this->camera->processKeyMovement();
			this->shader->sendUniformVec3("viewPos", this->camera->getEye());
			this->light->updatePosition(this->shader);
			glClearColor(0.f, 0.0f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			this->draw_objects();
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
