#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include "MeshEntry.h"
#include "Shader.h"

using namespace std;


class Mesh
{
private:
	vector<MeshEntry> meshes;
	string directory;
	void loadMesh(string path);
	void processNode(aiNode* node, const aiScene* scene);
	MeshEntry processMesh(aiMesh* mesh, const aiScene* scene);
public:
	Mesh(const float* points, int size, int count_vertex);
	Mesh(const char* path);
	void draw(Shader* shader);
};

