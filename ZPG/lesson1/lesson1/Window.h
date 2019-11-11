#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Window
{
private:
	GLFWwindow* window;
	void init();
public:
	Window();
	~Window();

	void getResolution(int* width, int* height);

	GLFWwindow* getWindow();
};

