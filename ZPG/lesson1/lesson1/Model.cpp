#include "Model.h"


void Model::createVBO()
{
	this->VBO;
	glGenBuffers(1, &this->VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->points, GL_STATIC_DRAW);
	cout << "VBO created" << endl;
}

void Model::createVAO()
{
	this->VAO;
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//
	glEnableVertexAttribArray(2); //UV
	//
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0); //nove kdyztakpredelat
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))); //nove kdyztakpredelet
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float))); //nove kdyztakpredelat
	cout << "VAO created" << endl;
}


GLuint Model::getVAO()
{
	return this->VAO;
}

int Model::getCountVertex()
{
	return this->count_vertex;
}

Model::Model(const float* points, int size)
{
	this->points = points;
	this->size = size;
	this->createVBO();
	this->createVAO();
	cout << "Model finished" << endl;
	this->count_vertex = (size / sizeof(float)) / 6;
}

Model::~Model()
{
}
