#pragma once
#include "Light.h"
class DirectionalLight :public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntens, GLfloat diffuIntensity,
		GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);
	void UseDirectionalLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation
		, GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	~DirectionalLight();


private:
	glm::vec3 direction;
};

