#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Camera.h"
#include "ShaderLoader.h"

using namespace std;

class Camera;
class Shader : ShaderLoader
{
private:

	Camera* camera;
	GLuint shaderProgram;
	bool createShader(const char* vertexPath, const char* fragmentPath);
	bool createShader();
	bool isCompileErrors(GLuint shader, string type);

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader();
	~Shader();
	void use();
	void updateCamera();
	void subscribeCamera(Camera* camera);

	void setUniform4f(const string& name, float value);
	void setUniform1f(const string& name, float value);
	void setUniform1i(const string& name, int value);
	void sendUniformVec4(const GLchar* name, glm::vec4 data);
	void sendUniformVec3(const GLchar* name, glm::vec3 data);
	void sendUniformMat4(const GLchar* name, glm::mat4 data);
};

