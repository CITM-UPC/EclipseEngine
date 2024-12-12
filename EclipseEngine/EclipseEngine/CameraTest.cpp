#include "CameraTest.h"

CameraTest::CameraTest()
{
    m_Position = glm::vec3(0.0f, 0.0f, 5.0f);
    m_Front = glm::vec3(-1.0f, -0.5f, 1.0f);
    m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
    UpdateViewMatrix();
}

void CameraTest::SetPerspective(float fov, float aspect, float nearClip, float farClip)
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
}

void CameraTest::SetOrthographic(float left, float right, float bottom, float top, float nearClip, float farClip) 
{
	m_ProjectionMatrix = glm::ortho(left, right, bottom, top, nearClip, farClip);
}

void CameraTest::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	UpdateViewMatrix();
}

void CameraTest::LookAt(const glm::vec3& target) 
{
	m_Front = glm::normalize(target - m_Position);
	UpdateViewMatrix();
}

void CameraTest::Move(const glm::vec3& delta)
{
	m_Position += delta;
	UpdateViewMatrix();
}

void CameraTest::UpdateViewMatrix() 
{
	m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

glm::mat4 CameraTest::GetViewMatrix() const 
{
	return m_ViewMatrix;
}