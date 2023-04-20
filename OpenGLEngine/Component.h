#pragma once

#include <memory>

class GameObject;

class Component
{
protected:
	GameObject* m_owner;

protected:
	Component() = delete;
	Component(GameObject* target) { m_owner = target; }

public:
	virtual void Destroy() = 0;
	virtual void Update(float deltaTime = 0) {};
};

