#pragma once

#include "Component.h"
#include "Model.h"
#include "Shader.h"

//stl
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightingModule;

class GameObject
{
protected:
	//Componentize : Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_forward;
	glm::vec3 m_scale;

	std::vector<Component*> m_components;
	std::shared_ptr<Model> m_pModel;

public:
	GameObject() = delete;
	GameObject(glm::vec3 pos);
	GameObject(glm::vec3 pos, const char* modelPath, const char* vertexShaderPath = "", const char* fragmentShaderPath = "");
	~GameObject();

public:
	//Transform
	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 Forward() { return m_forward; }
	glm::vec3 GetScale() { return m_scale; }
	glm::vec3 Right() { return glm::normalize(glm::cross(Forward(), (glm::vec3(0.0, 1.0, 0.0)))); }
	glm::vec3 Up() { return glm::normalize(glm::cross(Right(), Forward())); }
	glm::mat4 ModelMatrix();

	void SetPosition(glm::vec3 pos) { m_position = pos; }
	void SetRotation(glm::vec3 rot);
	virtual void SetForwardDirection(glm::vec3 rot);
	void SetScale(glm::vec3 scale) { m_scale = scale; }

	void AddComponent(Component* pComp) { m_components.push_back(pComp); }
	void SetModel(std::shared_ptr<Model> pModel) { m_pModel = pModel; }
	void SetModel(const char* modelPath) { /*TODO*/ }

	void Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, LightingModule* plightModule);


	virtual void Update(float deltaTime);

	virtual void Destroy();
};

