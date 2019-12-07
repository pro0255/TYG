#include "Mesh.h"

Mesh::Mesh(const float* points, int size, int count_vertex)
{
	this->meshes.push_back(MeshEntry(points, size, count_vertex));
}

Mesh::Mesh(const char* path)
{
	this->loadMesh(path);
}

void Mesh::draw(Shader* shader) //vykresleni jednotivych modelu ve velkem meshi
{
	for (unsigned int i = 0; i < this->meshes.size(); i++) {
		meshes.at(i).draw();
	}
}

void Mesh::loadMesh(string path)
{
	Assimp::Importer importer;
	unsigned int importOptions = aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_CalcTangentSpace;
	const aiScene* scene = importer.ReadFile(path, importOptions);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of("/"));
	processNode(scene->mRootNode, scene);
}


void Mesh::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

MeshEntry Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indicies;
	vector<Textures> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector;

		if (mesh->HasPositions()) {
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;
		}

		if (mesh->HasNormals()) {
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.Uv = vec;
		}
		else {
			vertex.Uv = glm::vec2(0.0f, 0.0f);
		}

		if (mesh->HasTangentsAndBitangents()) {
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
			// bitangent
		}
		vertices.push_back(vertex);



	}
	if (mesh->HasFaces()) {
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) {
				indicies.push_back(face.mIndices[j]);
			}
		}
	}

	for (unsigned int i = 0; i < scene->mNumMaterials; i++) {

		const aiMaterial* mat = scene->mMaterials[i];
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	return MeshEntry(vertices, indicies, textures);
}



