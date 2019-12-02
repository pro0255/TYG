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
	void draw();
	vector<Vertex> verticies;
	vector<unsigned int> indices;
	vector<Textures> textures;
	unsigned int VAO;

private:
	unsigned int VBO, EBO;
	void setupMeshEntry();
};

