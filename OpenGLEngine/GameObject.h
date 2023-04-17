#pragma once

#include "Shader.h"

//stl
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject
{
protected:
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_scale;

	glm::mat4 m_model;

	//Mesh
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_vertexBufferObject, m_elementBufferObject, m_vertexArrayObject;

	//Material
	Shader m_shaderProgram;
	std::vector<unsigned int> m_textureIDs;

public:
	GameObject();
	GameObject(glm::vec3 pos, bool useShader = false);
	~GameObject();

public:
	//Transform
	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 Forward() { return m_forward; }
	glm::vec3 GetScale() { return m_scale; }
	glm::vec3 Right() { return glm::normalize(glm::cross(m_forward, (glm::vec3(0.0, 1.0, 0.0)))); }
	glm::vec3 Up() { return glm::cross(m_forward, Right()); }
	glm::mat4 Model();

	void SetPosition(glm::vec3 pos) { m_position = pos; }
	virtual void SetForwardDirection(glm::vec3 rot) { m_forward = rot; }
	void SetScale(glm::vec3 scale) { m_scale = scale; }

	//Mesh TODO: Componentize this : mesh class
	float* GetVertices() { return m_vertices.size() > 0? &m_vertices[0] : nullptr; }
	unsigned int* GetTextures() { return m_textureIDs.size() > 0 ? &m_textureIDs[0] : nullptr; }
	void SetVertices(float verts[]);
	void SetVertices(std::vector<float> verts);
	unsigned int VAO() { return m_vertexArrayObject; }
	unsigned int VBO() { return m_vertexBufferObject; }
	unsigned int EBO() { return m_elementBufferObject; }

	//Shader/Mat TODO: Componentize : Material
	Shader& GetShader() { return m_shaderProgram; }

	virtual void Update();

	virtual void Destroy();
private:
	void InitMesh();
	void InitTexture();
	void UpdateTransform();
};

