#pragma once

#include "LightingModule.h"

#include "GameObject.h"
#include "LightingModule.h"
#include "Camera.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Scene
{
private:
	std::vector<shared_ptr<GameObject>> m_gameObects;
	LightingModule m_lightingModule;
	shared_ptr<Camera> m_mainCamera;

public:

	shared_ptr<GameObject> AddGameObject(shared_ptr<GameObject> obj) { m_gameObects.push_back(obj); return obj; }
	shared_ptr<GameObject> AddGameObject(glm::vec3 pos, const char* modelPath, const char* vertPath, const char* fragPath) { m_gameObects.emplace_back(make_shared<GameObject>(pos, modelPath, vertPath, fragPath)); return m_gameObects[m_gameObects.size() - 1]; }
	void RemoveGameObject(shared_ptr<GameObject> obj);

	void SetMainCamera(shared_ptr<Camera> cam) { m_mainCamera = cam; }

	shared_ptr<DirectionalLight> AddLight(shared_ptr<DirectionalLight> light) { return m_lightingModule.SetDirectionalLight(light); }
	shared_ptr<DirectionalLight> AddLight(glm::vec3 direction, LightColorData data) { return  m_lightingModule.SetDirectionalLight(direction, data); }
	shared_ptr<PointLight> AddLight(shared_ptr<PointLight> light) { AddGameObject(shared_ptr<GameObject>( light.get())); return m_lightingModule.AddPointLight(light); }
	shared_ptr<PointLight> AddLight(glm::vec3 position, LightColorData colorData, LightAttenuationData attentuationData) { return std::static_pointer_cast<PointLight>( AddGameObject(shared_ptr<GameObject>(m_lightingModule.AddPointLight(position, colorData, attentuationData).get()))); }
	shared_ptr<SpotLight> AddLight(shared_ptr<SpotLight> light) { return m_lightingModule.SetSpotLight(light); }
	shared_ptr<SpotLight> AddLight(glm::vec3 position, glm::vec3 dir, LightColorData colorData, LightAttenuationData attentuationData, float cutoff, float outerCutoff) { return m_lightingModule.SetSpotLight(position, dir, colorData, attentuationData, cutoff, outerCutoff); }

	void Draw(glm::ivec2 windowDimensions);
	void Update(float deltaTime);
	void Destroy();

};

