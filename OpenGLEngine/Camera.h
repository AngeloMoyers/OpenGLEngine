#pragma once
#include "GameObject.h"
class Camera :
    public GameObject
{
private:
    glm::mat4 m_view;
    glm::vec3 m_ypr;
    float m_fov;

    glm::vec2 m_lastMousePos;

    float m_turnSensitivity;
    bool m_firstMouseframe = true;
public:
    Camera(glm::vec2 screenSize);
public:
    void LookAt(glm::vec3 target);
    void LookAt(GameObject* target);

    glm::mat4 GetView() { return Model(); }
    float GetFOV() { return m_fov; }
    void SetFOV(float _fov) {m_fov = _fov;}

    virtual void SetForwardDirection(glm::vec3 rot) override;

    void UpdateMouseInput(glm::vec2 mPos);
private:
    void UpdateCameraAngle();
    void UpdateYPR();
};

