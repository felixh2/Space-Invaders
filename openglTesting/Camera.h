#pragma once
#include <glew.h>
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include <glfw3.h>

class Camera
{
public:
	Camera(glm::vec3 initialPosition, glm::vec3 initialUp, GLfloat initialYaw, 
			GLfloat initialPitch, GLfloat initialMoveSpeed, GLfloat initialTurnSpeed);

	void Update();
	glm::vec3 GetPosition();
	void KeyControl(bool* keys, GLfloat deltaTime);
	void MouseControl(GLfloat xChange, GLfloat yChange );
	glm::mat4 CalculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat turnSpeed;
};

