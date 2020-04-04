#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntens, GLfloat diffuIntensity,
				GLfloat xPos, GLfloat yPos, GLfloat zPos,
				GLfloat con, GLfloat lin, GLfloat quad);

	void UsePointLight(GLfloat ambientItensityLocation, 
						GLfloat ambientColorLocation,
						GLfloat diffuseIntensityLocation,
						GLfloat positionLocation, 
						GLfloat constantLocation,
						GLfloat linearLocation,
						GLfloat quadraticLocation);

	~PointLight();

private:
	glm::vec3 position;
	GLfloat constant, linear, quadratic;
};

