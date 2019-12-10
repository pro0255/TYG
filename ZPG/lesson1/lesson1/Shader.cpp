#include "Shader.h"
#include "Application.h"

//Shader with path
Shader::Shader(const char* vertexPath, const char* fragmentPath) { this->shaderProgram = this->loadShader(vertexPath, fragmentPath); this->camera = nullptr; }
//Default Shader
Shader::Shader() : Shader("./shaders/vertex.glsl", "./shaders/fragment.glsl") {}

void Shader::reset() { glUseProgram(0); }

void Shader::use() { glUseProgram(this->shaderProgram); }

void Shader::updateCamera()
{
	if (camera != nullptr) {
		this->sendUniformMat4("projectionMatrix", this->camera->getProjectionMatrix());
		this->sendUniformMat4("viewMatrix", camera->getCamera());
	}
	else {
		cout << "Camera in SHADER is nullptr" << endl;
	}
}

void Shader::subscribeCamera(Camera* camera)
{
	this->camera = camera;
	cout << "Subscribing camera!" << endl;
}

void Shader::setUniform4f(const string& name, float value)
{
	glUniform4f(glGetUniformLocation(this->shaderProgram, name.c_str()), 0.0f, value, value, value);
}

void Shader::setUniform1f(const string& name, float value)
{
	glUniform1f(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}

void Shader::setUniform1i(const string& name, int value)
{
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}

void Shader::sendUniformVec4(const GLchar* name, glm::vec4 data)
{
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniform4f(uniformID, data.x, data.y, data.z, data.w);
	}
	else {
		cout << "In shader does not exist uniform value with this value or is not used.." << endl;
	}
}

void Shader::sendUniformVec3(const GLchar* name, glm::vec3 data)
{
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniform3f(uniformID, data.x, data.y, data.z);
	}
	else {
		cout << "In shader does not exist uniform value with this value or is not used.." << endl;

	}
}


void Shader::sendUniformMat4(const GLchar* name, glm::mat4 data)
{
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniformMatrix4fv(uniformID, 1, GL_FALSE, glm::value_ptr(data));
	}
	else {
		cout << "In shader does not exist uniform value with this value or is not used.." << endl;
	}
}

Shader::~Shader()
{


}
