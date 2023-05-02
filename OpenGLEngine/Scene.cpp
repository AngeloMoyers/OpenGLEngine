#include "Scene.h"

void Scene::RemoveGameObject(shared_ptr<GameObject> obj)
{
	auto it = std::find(m_gameObects.begin(), m_gameObects.end(), obj);
	if (it != m_gameObects.end())
		m_gameObects.erase(it);
}

void Scene::Draw(glm::ivec2 windowDimensions)
{
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(m_mainCamera->GetFOV()), (float)windowDimensions.x / (float)windowDimensions.y, 0.1f, 100.0f);

	for (int i = 0; i < m_gameObects.size(); i++)
	{
		m_gameObects[i]->Draw(projection, m_mainCamera->GetView(), &m_lightingModule);
	}
}

void Scene::Update(float deltaTime)
{
	for (int i = 0; i < m_gameObects.size(); i++)
	{
		m_gameObects[i]->Update(deltaTime);
	}
}

void Scene::Destroy()
{
	for (int i = 0; i < m_gameObects.size(); i++)
	{
		m_gameObects[i]->Destroy();
	}
}
