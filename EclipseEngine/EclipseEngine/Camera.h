#ifndef CAMERA_H
#define CAMERA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"
#include "Component.h"

class Camera 
{
public:
	Camera(int widht, int height, glm::vec3 position);

	//void Update() override;

	void UpdateMatrix(float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window); //C
	glm::mat4 GetProjectionMatrix() { return projection; }

	// Static scroll callback function
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); //C
	glm::vec3 GetRaycastHitPoint(GLFWwindow* window);

public:
	glm::vec3 Position;                                       // Camera's position
	glm::vec3 Orientation = glm::vec3(-1.0f, -0.5f, 1.0f);     // Camera's orientetion
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);               // Camera's up vector (Y)
	glm::vec3 targetPosition = glm::vec3(0.0f, 0.0f, 0.0f);	  // Orbit target position (default origin)
	glm::mat4 cameraMatrix = glm::mat4(1.0f);				 // Camera's matrix
	glm::mat4 projection = glm::mat4(1.0f);					 // Camera's projection matrix
	bool firstClick = true; //C

	int width;
	int height;
	float nearPlane;
	float farPlane;

	float speed = 0.1f; //C
	float sensitivity = 100.0f; //C
	float FOVdeg = 45.0f;   // Field of View, adjustable for zoom

	static float scrollOffset;  //C
};

#endif //CAMERA_H