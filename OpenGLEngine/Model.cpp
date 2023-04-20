#include "Model.h"

#include <stdexcept>

#include "STB.h"

Model::Model(GameObject* owner, const char* modelPath, const char* vertShaderPath, const char* fragShaderPath)
	:Component(owner)
	,m_pShader(ShaderFactory::LoadShader(vertShaderPath, fragShaderPath))
{
	LoadModel(modelPath);
}

void Model::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix)
{
	m_pShader->Use();
	m_pShader->SetMat4("projection", projectionMatrix);
	m_pShader->SetMat4("view", viewMatrix);
	m_pShader->SetMat4("model", modelMatrix);

	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Draw(*m_pShader);
	}
}

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		throw std::runtime_error("Assimp Error: ");
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* pMesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(ProcessMesh(pMesh, scene));
	}

	for (int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> verts;
	std::vector<unsigned int> inds;
	std::vector<Texture> texs;

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vert;

		glm::vec3 vec;
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vert.Position = vec;

		if (mesh->HasNormals())
		{
			glm::vec3 norm;
			norm.x = mesh->mNormals[i].x;
			norm.y = mesh->mNormals[i].y;
			norm.z = mesh->mNormals[i].z;
			vert.Normal = norm;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 tex;
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
			vert.TexCoords = tex;
		}
		else
		{
			vert.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		verts.push_back(vert);
	}

	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (int j = 0; j < face.mNumIndices; j++)
		{
			inds.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuseTexture");
		texs.insert(texs.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specularTexture");
		texs.insert(texs.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(verts, inds, texs);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> texs;

	for (int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;

		for (int j = 0; j < m_loadedTextures.size(); j++)
		{
			if (std::strcmp(m_loadedTextures[j].path.data(), str.C_Str()) == 0)
			{
				texs.push_back(m_loadedTextures[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture tex;
			tex.ID = TextureFromFile(str.C_Str(), m_directory);
			tex.type = typeName;
			tex.path = str.C_Str();
			texs.push_back(tex);
			m_loadedTextures.push_back(tex);
		}
	}
	return texs;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{
	stbi_set_flip_vertically_on_load(true);

	std::string filename = directory + "/" + path;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

void Model::Destroy()
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Destroy();
	}
	m_pShader->Destroy();
}


