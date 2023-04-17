#include "Camera.h"

Camera::Camera(glm::vec2 screenSize)
	:GameObject(glm::vec3(0.0,0.0,0.0))
	,m_ypr(glm::vec3( 0.0f, 0.0f, 0.0f))
	,m_turnSensitivity(0.1f)
{
	m_lastMousePos.x = screenSize.x / 2.0f;
	m_lastMousePos.y = screenSize.y / 2.0f;
}

void Camera::LookAt(glm::vec3 target)
{
	m_model = glm::lookAt(m_position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::LookAt(GameObject* target)
{
	m_model = glm::lookAt(m_position, target->GetPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::SetForwardDirection(glm::vec3 rot)
{
	GameObject::SetForwardDirection(rot);
	UpdateYPR();
}

void Camera::UpdateMouseInput(glm::vec2 mPos)
{
	if (m_firstMouseframe)
	{
		if (mPos == glm::vec2(0.0f, 0.0f))
			return;

		m_lastMousePos = mPos;

		m_firstMouseframe = false;
	}

	float xOffset = mPos.x - m_lastMousePos.x;
	float yOffset = m_lastMousePos.y - mPos.y;

	m_lastMousePos = mPos;

	xOffset *= m_turnSensitivity;
	yOffset *= m_turnSensitivity;

	m_ypr.x += xOffset;
	m_ypr.y += yOffset;

	if (m_ypr.y > 89.0f)
		m_ypr.y = 89.0f;
	if (m_ypr.y < -89.0f)
		m_ypr.y = -89.0f;

	UpdateCameraAngle();
}

void Camera::UpdateCameraAngle()
{
	m_forward.x = cos(glm::radians(m_ypr.x)) * cos(glm::radians(m_ypr.y));
	m_forward.y = sin(glm::radians(m_ypr.y));
	m_forward.z = sin(glm::radians(m_ypr.x)) * cos(glm::radians(m_ypr.y));
	m_forward = normalize(m_forward);
}

void Camera::UpdateYPR()
{
	m_ypr.y = glm::degrees(-asin(glm::dot(m_forward, glm::vec3(0.0f, 1.0f, 0.0f))));
	glm::vec3 normForward = normalize(glm::vec3(m_forward.x, 0.0f, m_forward.z));
	m_ypr.x = glm::degrees(acos(dot(normForward, glm::vec3(1.0f, 0.0f, 0.0f))));
}
