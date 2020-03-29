#pragma once
#include<glew.h>
#include <glm/glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntens,
		GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,GLfloat diffuIntensity);
	void UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation
	, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity;

	// directional light
	glm::vec3 direction;
	GLfloat diffuseIntesity;
};

