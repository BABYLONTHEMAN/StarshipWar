#include "MeshGroups.h"



MeshGroups::MeshGroups()
{
}

////////RenderModel
void MeshGroups::RenderModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		unsigned int shtIndex = meshToTex[i];
		if (shtIndex < textureList.size() && textureList[shtIndex])
		{
			textureList[shtIndex]->useTexture();
		}
		meshList[i]->RenderMesh();
	}
}
////////

/////////////////////////////////////////////////////****************************************
//LoadModel
/////////////////////////////////////////////////////****************************************
void MeshGroups::LoadModel(const std::string & filename)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs |
		aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		printf("scene or Model is failed to Load : %s",filename,importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode,scene);
	LoadSht(scene);
}
//....................
/////////////////////////////////////////////////////****************************************
//LoadNode
/////////////////////////////////////////////////////****************************************
void MeshGroups::LoadNode(aiNode * node, const aiScene * scene)
{
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}
	/////
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}
/////////////////////////////////////////////////////****************************************
//LoadMesh
/////////////////////////////////////////////////////****************************************
void MeshGroups::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y});
		}
		else
		{
			vertices.insert(vertices.end(), { 0.0f,0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z }); // instead of Negative sign -
	}																									//you can  do this ... put - 
																											// in Frag shader ... like -normalize(direction)),0.0f);
		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
	
		Mesh* newMesh = new Mesh();
		newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
		meshList.push_back(newMesh);
		meshToTex.push_back(mesh->mMaterialIndex);
	
}
/////////////////////////////////////////////////////****************************************
//LoadSht
void MeshGroups::LoadSht(const aiScene * scene)
{
	textureList.resize(scene->mNumMaterials);

	for (size_t i = 0; i < scene -> mNumMaterials; i++)
	{
		aiMaterial* sht = scene->mMaterials[i];
	
	textureList[i] = nullptr; //it means Null Pointer

	if (sht->GetTextureCount(aiTextureType_DIFFUSE))
	{
		aiString path;
		if (sht->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			int idx = std::string(path.data).rfind("\\"); //back slash is ESCAPE character so 2 of them means escape twice 
			std::string filename = std::string(path.data).substr(idx + 1);

			std::string texPath = std::string("Textures/") + filename;
			textureList[i] = new Texture(texPath.c_str());

			//if TextureA alpha stuff is failed or not .....
			if (!textureList[i]->LoadTexture())
			{
				printf("Failed to load texture ... %s\n", texPath);
				delete textureList[i];
				textureList[i] = nullptr;
			}
		}
	}
	if (!textureList[i])
	{
			textureList[i] = new Texture("Textures/plain.png");
			textureList[i]->LoadTextureA();

	}
}
}
/////////////////////////////////////////////////////****************************************
// endOfLoadSht


//////// ClearModel
void MeshGroups::ClearModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}


	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}
	


MeshGroups::~MeshGroups()
{
}
