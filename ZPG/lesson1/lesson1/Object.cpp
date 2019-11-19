#include "Object.h"
#include <iostream>
using namespace std;



int Object::GENERATE_ID = 0;

glm::mat4 Object::getModelMatrix()
{
	return this->modelMatrix;
}

int Object::getCountVertex()
{
	return this->model->getCountVertex();
}

void Object::bind()
{
	glBindVertexArray(model->getVAO());
	this->texture->bind(); //bind textury
}

int Object::getId()
{
	return this->id;
}

glm::vec4 Object::getObjectColor()
{
	return this->color;
}

void Object::rotateObject(float angle, glm::vec3 vector)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, angle, vector);
}

void Object::translateObject(glm::vec3 vector)
{
	this->modelMatrix = glm::translate(this->modelMatrix, vector);
}

void Object::scaleObject(glm::vec3 vector)
{
	this->modelMatrix = glm::scale(this->modelMatrix, vector);
}

void Object::resetObject()
{
	this->modelMatrix = glm::mat4(1.0f);
}

void Object::set_shader_properties(Shader* shader)
{
	shader->sendUniformMat4("modelMatrix", this->modelMatrix);
	shader->sendUniformVec4("objectColor", this->color);
	texture->set_shader_properties(shader);
}

Object::Object(Model* model)
{
	this->id = ++GENERATE_ID;
	this->model = model;
	this->color = glm::vec4(0.385, 0.647, 0.812, 1.0);
	this->resetObject();
	this->texture = new Texture();
}


Object::Object(Model* model, glm::vec4 color)
{
	this->id = ++GENERATE_ID;
	this->model = model;
	this->color = color;
	this->resetObject();
}

Object::~Object()
{
}
