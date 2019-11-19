#include "Shader.h"
#include "Application.h"



const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 position;"
"layout(location=1) in vec3 normal;"
"uniform mat4 modelMatrix;" //poslani matice dovnitr
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"void main () {"
"     gl_Position = (projectionMatrix*viewMatrix*modelMatrix) * vec4(position, 1.0);"
"}";

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"uniform vec4 ourColor;"
"void main () {"
"     frag_colour = ourColor;"
"}";


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	if (!this->createShader(vertexPath, fragmentPath)) {
		throw "Program Shader Failed Compiled";
	}
}

Shader::Shader()
{
	this->shaderProgram = this->loadShader("./shaders/vertex.glsl", "./shaders/fragment.glsl");
	/*
	if (!this->createShader()) {
		throw "Program Shader Failed Compiled";
	}
	*/
	cout << " Tady jsem spravne vytvoril shader " << endl;
}

bool Shader::createShader(const char* vertexCode, const char* fragmentCode)
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	if (this->isCompileErrors(vertexShader, "SHADER")) return false;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	if (this->isCompileErrors(fragmentShader, "SHADER")) return false;

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, fragmentShader);
	glAttachShader(this->shaderProgram, vertexShader);
	glLinkProgram(this->shaderProgram);

	if (this->isCompileErrors(this->shaderProgram, "PROGRAM")) return false;
	return true;
}

bool Shader::createShader()
{
	if (this->createShader(vertex_shader, fragment_shader)) return true;
	return false;
}


bool Shader::isCompileErrors(GLuint shader, string type)
{
	GLint status;
	if (type == "PROGRAM") {
		glGetProgramiv(shader, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLogLength;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(shader, infoLogLength, NULL, strInfoLog);

			fprintf(stderr, "\n===========================================================\nLinker failure: %s\n", strInfoLog);

			printf("Something bad happend with vertex shader or fragment shader \n %s===========================================================\ \n", strInfoLog);
			delete[] strInfoLog;
			return true;
		}
		return false;
	}
	else {
		glGetShaderiv(shader, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLogLenght;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLenght);
			GLchar* strInfoLog = new GLchar[infoLogLenght + 1];
			glGetShaderInfoLog(shader, infoLogLenght, NULL, strInfoLog);
			fprintf(stderr, "\n======================================\nLinker failure: %s\n", strInfoLog);

			printf("Something bad happend with vertex shader or fragment shader \n %s ===================================== \n", strInfoLog);
			delete[] strInfoLog;
			return true;
		}
		return false;
	}
}

void Shader::use()
{
	glUseProgram(this->shaderProgram);
}

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
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), 0);
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
