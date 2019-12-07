#pragma once
#include <string>
#include <vector>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/vec2.hpp>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Uv;
	glm::vec2 Tangent;
};

struct Textures {
	unsigned int id;
	string type;
	string path;
};

class MeshEntry
{
public:
	MeshEntry(vector<Vertex> vectices, vector<unsigned int> indices, vector<Textures> textures);
	MeshEntry(const float* points, int size, int count_vertex);
	void draw();
private:
	void setupMesh(vector<Vertex> vectices, vector<unsigned int> indices, vector<Textures> textures);
	void setupMesh(const float* points, int size, int count_vertex);
	bool isOld;
	int count_vertex;
	unsigned int VAO;
};

