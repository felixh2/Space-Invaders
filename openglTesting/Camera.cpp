#include "Camera.h"
#include <stdio.h>



Camera::Camera(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, GLfloat initialPitch, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed)
{
	position = initialPosition;
	worldUp = initialUp;
	yaw = initialYaw;
	pitch = initialPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = initialMoveSpeed;
	turnSpeed = initialTurnSpeed;

	Update();
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * sin(glm::radians(pitch));
	front.y = cos(glm::radians(pitch));
	front.z= -sin(glm::radians(yaw) * sin(glm::radians(pitch)));
	front = glm::normalize(front);
	
	printf("%0.2f, %0.2f, %0.2f\n", front.x, front.y, front.z);
	
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front)); 
}

glm::vec3 Camera::GetPosition()
{
	return position;
}

void Camera::KeyControl(bool * keys, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

}

void Camera::MouseControl(GLfloat xChange, GLfloat yChange)
{
	yaw -= xChange * turnSpeed;
	pitch -= yChange * turnSpeed;



	front.x = cos(glm::radians(yaw)) * sin(glm::radians(pitch));
	front.y = cos(glm::radians(pitch));
	front.z = -sin(glm::radians(yaw) * sin(glm::radians(pitch)));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::CalculateViewMatrix()
{
	
	//return glm::mat4(1.0f);
	return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{


}
