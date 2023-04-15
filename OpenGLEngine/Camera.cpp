#include "Camera.h"

Camera::Camera()
	:GameObject(glm::vec3(0.0,0.0,-3.0))
{

}

void Camera::LookAt(glm::vec3 target)
{
	m_view = glm::lookAt(m_position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::LookAt(GameObject* target)
{
}
