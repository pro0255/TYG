#include "Application.h"
#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Object.h"

using namespace std;


glm::mat4 M = glm::mat4(1.0f);

glm::mat4 Rotation = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

glm::mat4 Rot = glm::rotate(M, 90.0f, glm::vec3(1.0f, 1.0f, 0.0f));
glm::mat4 Translate = glm::translate(M, glm::vec3(1.0f, 1.0f, 0.0f));
glm::mat4 Scale = glm::scale(M, glm::vec3(2.5f));



float points[] = {
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f
};



Application* Application::instance = nullptr;


Application::~Application()
{
	delete instance;
	instance = nullptr;
	cout << "Destraction of the object Application runed well." << endl;
}


Application* Application::getInstance()
{
	if (instance == nullptr) {
		instance = new Application();
		instance->window = new Window();
		instance->scene = new Scene(instance->window->getWindow());
		instance->setCallbacks();
	}
	return instance;
}


void Application::run()
{
	glfwGetCursorPos(this->window->getWindow(), &this->lastX, &this->lastY);
	Renderer::draw_scene(this->scene);
}

void Application::destroyWindow()
{
	glfwDestroyWindow(this->window->getWindow());
	glfwTerminate();
}

GLFWwindow* Application::getWindow()
{
	return this->window->getWindow();
}

void Application::setCallbacks()
{
	glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description);  });

	glfwSetKeyCallback(this->window->getWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });

	glfwSetCursorPosCallback(this->window->getWindow(), [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_callback(window, mouseXPos, mouseYPos); });

	glfwSetMouseButtonCallback(this->window->getWindow(), [](GLFWwindow* window, int button, int action, int mode)-> void {Application::getInstance()->button_callback(window, button, action, mode);  });

	glfwSetWindowFocusCallback(this->window->getWindow(), [](GLFWwindow* window, int focused)->void {Application::getInstance()->window_focus_callback(window, focused);  });

	glfwSetWindowIconifyCallback(this->window->getWindow(), [](GLFWwindow* window, int iconified)->void {Application::getInstance()->window_iconify_callback(window, iconified); });

	glfwSetWindowSizeCallback(this->window->getWindow(), [](GLFWwindow* window, int width, int height)->void {Application::getInstance()->window_size_callback(window, width, height); });

	glfwSetScrollCallback(this->window->getWindow(), [](GLFWwindow* window, double x, double y)->void {Application::getInstance()->scroll_callback(window, x, y); });
}

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
		//scene->getCamera()->keyMove(FORWARD);
		scene->getCamera()->pressMove(FORWARD);
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
		//scene->getCamera()->keyMove(RIGHT);
		scene->getCamera()->pressMove(RIGHT);
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
		//scene->getCamera()->keyMove(BACK);
		scene->getCamera()->pressMove(BACK);
	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_RELEASE)) {
		//scene->getCamera()->keyMove(LEFT);
		scene->getCamera()->pressMove(LEFT);
	}
	else if (key == GLFW_KEY_T && (action == GLFW_PRESS)) {
		scene->scaleObject();
	}
	else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		glfwSetInputMode(instance->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	}
	else if (key == GLFW_KEY_C && action == GLFW_RELEASE) {
		glfwSetInputMode(instance->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_focus_callback(GLFWwindow* window, int focused)
{
	printf("window_focus_callback \n");
}

void Application::window_iconify_callback(GLFWwindow* window, int iconified)
{
	printf("window_iconify_callback \n");
}

void Application::window_size_callback(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_callback(GLFWwindow* window, double x, double y)
{
	float xOffSet = x - this->lastX;
	float yOffSet = this->lastY - y;

	this->lastX = x;
	this->lastY = y;

	this->scene->getCamera()->mouseMove(xOffSet, yOffSet);
	//printf("cursor_callback \n");
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (action == GLFW_RELEASE) {
		instance->scene->selected_Object_Id = -1;
		cout << "released" << endl;
	}


	double _x = 0;
	double _y = 0;

	int height = 0;
	int width = 0;
	if (action == GLFW_PRESS) {

		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		glfwGetCursorPos(this->window->getWindow(), &_x, &_y);
		int x = _x;
		int y = _y;
		this->instance->window->getResolution(&width, &height);

		int newy = height - y;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %d\n", x, y, color[0], color[1], color[2], color[3], depth, index);


		glm::vec3 screenX = glm::vec3(x, newy, depth);
		glm::mat4& view = instance->scene->getCamera()->viewMatrix;
		glm::mat4& projection = instance->scene->getCamera()->projectionMatrix;


		glm::vec4 viewPort = glm::vec4(0, 0, width, height);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);

		instance->scene->selected_Object_Id = index;
		printf("unproject [%f, %f, %f]\n", pos.x, pos.y, pos.z);

		if (button == 1) {
			scene->createObject(pos);
		}
	}
}

void Application::scroll_callback(GLFWwindow* window, double x, double y)
{
	this->scene->getCamera()->scrollMove(y);
}

void Application::getVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}
