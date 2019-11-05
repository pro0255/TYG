//Include GLFW  
//Jedna z moznosti jak pridat knihovny, nebo v vlastnostech..
//#pragma comment (lib, "opengl32.lib")
//#pragma comment (lib, "glu32.lib")
//#pragma comment (lib, "glew32.lib")
//#pragma comment (lib, "glfw3.lib")
/*
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
*/
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>

#include "Application.h"
#include "Shader.h"
#include <iostream>
#include <fstream>



using namespace std;




int main(void) {
	Application::getInstance()->run();
}