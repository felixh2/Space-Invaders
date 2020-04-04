#pragma once
#include<glew.h>
#include <glm/glm.hpp>
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntens, GLfloat diffuIntensity);
	//virtual void UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation);
	~Light();

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntesity;
};

