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
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	Shader m_shaderProgram;

	float* m_vertices;

public:
	GameObject();
	GameObject(glm::vec3 pos);
public:
	//Transform
	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetRotation() { return m_rotation; }
	glm::vec3 GetScale() { return m_scale; }
	glm::vec3 Right() { glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), m_rotation)); }
	glm::vec3 Up() { return glm::cross(m_rotation, Right()); }

	//Mesh TOOD: Componentize this : mesh class
	float* GetVertices() { return m_vertices != nullptr ? & m_vertices[0] : nullptr; }
	void SetVertices(float* verts) { m_vertices = verts; }
};

