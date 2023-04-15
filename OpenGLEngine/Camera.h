#pragma once
#include "GameObject.h"
class Camera :
    public GameObject
{
private:
    glm::mat4 m_view;
public:
    Camera();
public:
    void LookAt(glm::vec3 target);
    void LookAt(GameObject* target);

    glm::mat4 GetView() { return m_view; }
};

