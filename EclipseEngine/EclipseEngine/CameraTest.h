#ifndef CAMERA_TEST_H
#define CAMERA_TEST_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraTest
{
public:
	CameraTest();
	void SetPerspective(float fov, float aspect, float nearClip, float farClip);
	void SetOrthographic(float left, float right, float bottom, float top, float nearClip, float farClip);
	void SetPosition(const glm::vec3& position);
	void LookAt(const glm::vec3& target);
	void Move(const glm::vec3& delta);
	void UpdateViewMatrix();

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

private:

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;

	float m_Speed;
	float m_Sensitivity;
	float m_Zoom;
};


#endif // !CAMERA_TEST_H
