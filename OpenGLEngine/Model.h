#pragma once

#include "Component.h"
#include "Mesh.h"
#include "ShaderFactory.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <memory>

using std::shared_ptr;
using std::make_shared;

class Model : Component
{
private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	std::vector<Texture> m_loadedTextures;

	shared_ptr<Shader> m_pShader;

public:
	Model(GameObject* owner, const char* modelPath, const char* vertShaderPath = "", const char* fragShaderPath = "");
	

private:
	void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix);
	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory);
	
	//Friends :)
	friend class GameObject;

	//Component
public:
	virtual void Destroy() override;
};

