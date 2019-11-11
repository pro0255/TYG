#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Window.h"
#include "Scene.h"
#include "Renderer.h"
#include "MovementEnum.h"
#pragma once


class Application
{

private:
	static Application* instance;
	Window* window;
	Scene* scene;
	void setCallbacks();
	bool firstMouse;

	double lastX;
	double lastY;


public:
	//Constructor and Destructor
	~Application();
	static Application* getInstance(); //Singleton



	//Callbacks
	void error_callback(int error, const char* description);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void window_focus_callback(GLFWwindow* window, int focused);
	void window_iconify_callback(GLFWwindow* window, int iconified);
	void window_size_callback(GLFWwindow* window, int width, int height);
	void cursor_callback(GLFWwindow* window, double x, double y);
	void button_callback(GLFWwindow* window, int button, int action, int mode);
	void scroll_callback(GLFWwindow* window, double x, double y);

	//Getters
	void getVersionInfo();
	GLFWwindow* getWindow();


	//Run Method
	void run();
	void destroyWindow();
};

