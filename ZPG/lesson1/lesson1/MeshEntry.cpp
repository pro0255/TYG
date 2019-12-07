#include "MeshEntry.h"
#include <GL\glew.h>

MeshEntry::MeshEntry(vector<Vertex> vectices, vector<unsigned int> indices, vector<Textures> textures)
{
	setupMesh(vectices, indices, textures);

	/*
	this->verticies = vectices;
	this->indices = indices;
	this->textures = textures;
	this->size = -1;
	setupMeshEntry();
	*/
}


MeshEntry::MeshEntry(const float* points, int size, int count_vertex)
{
	setupMesh(points, size, count_vertex);
	/*
	this->points = points;
	this->size = size;
	this->count_vertex = count_vertex;
	setupMeshEntry();
	*/
}

//ToDo: Doladit bere starou cast z toho, nastavit stencil buffer atd..

void MeshEntry::draw()
{
	glBindVertexArray(this->VAO);
	if (size == -1) {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, this->count_vertex);
	}
	glBindVertexArray(0);
}

void MeshEntry::setupMeshEntry()
{
	VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (this->size == -1) {
		glBufferData(GL_ARRAY_BUFFER, this->verticies.size() * sizeof(Vertex), &verticies[0], GL_STATIC_DRAW);
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, this->size, this->points, GL_STATIC_DRAW);
	}

	this->VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(this->VAO);


	if (this->size == -1) {
		//glBindBuffer(GL_ARRAY_BUFFER, this->VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0)); //pozice

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Normal))); //normaly

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Uv))); //uv

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, Tangent))); //tangenty
	}
	else {
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2); //UV

		glBindBuffer(GL_ARRAY_BUFFER, this->VAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0); //nove kdyztakpredelat
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))); //nove kdyztakpredelet
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float))); //nove kdyztakpredelat
	}


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);
	glBindVertexArray(0);
}

void MeshEntry::setupMesh(vector<Vertex> vectices, vector<unsigned int> indices, vector<Textures> textures)
{

	this->isOld = false;
	this->count_vertex = indices.size();

	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(Vertex), &vectices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	// Texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Uv));

	// Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));


}

void MeshEntry::setupMesh(const float* points, int size, int count_vertex)
{
	this->isOld = true;
	this->count_vertex = count_vertex;

	//Creation of Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);


	//Creation of Vertex Array Object
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);	//position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))); //normal
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float))); //uv
}



