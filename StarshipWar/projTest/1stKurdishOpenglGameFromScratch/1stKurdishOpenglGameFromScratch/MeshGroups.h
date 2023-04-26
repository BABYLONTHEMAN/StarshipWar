#pragma once
#include<vector>
#include<string>

#include<assimp\Importer.hpp>
#include<assimp\scene.h>
#include<assimp\postprocess.h>

#include "Mesh.h"
#include"Texture.h"

class MeshGroups
{
public:
	MeshGroups();

	void LoadModel(const std::string& filename);
	void RenderModel();
	void ClearModel();

	~MeshGroups();

private:
	void LoadNode(aiNode *node, const aiScene *scene);
	void LoadMesh(aiMesh *mesh, const aiScene *scene);
	void LoadSht(const aiScene *scene);
	std::vector<Mesh*> meshList;
	std::vector<Texture*> textureList;
	std::vector<unsigned int> meshToTex;

};

