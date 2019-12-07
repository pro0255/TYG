#include "ObjectAssimp.h"

int ObjectAssimp::GENERATE_ID = 5;

void ObjectAssimp::rotateObject(float angle, glm::vec3 vector)
{
	this->modelMatrix = glm::rotate(this->modelMatrix, angle, vector);
}

void ObjectAssimp::translateObject(glm::vec3 vector)
{
	this->modelMatrix = glm::translate(this->modelMatrix, vector);
}

void ObjectAssimp::scaleObject(glm::vec3 vector)
{
	this->modelMatrix = glm::scale(this->modelMatrix, vector);
}

void ObjectAssimp::resetObject()
{
	this->modelMatrix = glm::mat4(1.0f);
}

void ObjectAssimp::set_shader_properties(Shader* shader)
{
	shader->use();
	shader->sendUniformMat4("modelMatrix", this->modelMatrix);
	shader->sendUniformVec4("objectColor", this->color);
	this->texture->set_shader_properties(shader);
}

ObjectAssimp::ObjectAssimp(Mesh* mesh) : ObjectAssimp(mesh, glm::vec4(1.0, 1.0, 1.0, 1.0))
{
}

ObjectAssimp::ObjectAssimp(Mesh* mesh, glm::vec4 color)
{
	resetObject();
	//this->texture = new Texture();
	this->mesh = mesh;
	this->color = color;
	this->id = ObjectAssimp::GENERATE_ID++;
}

void ObjectAssimp::draw(Shader* shader)
{
	this->set_shader_properties(shader);
	this->mesh->draw(shader);
}
