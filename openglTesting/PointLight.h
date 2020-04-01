#pragma once
#include<glew.h>
#include <glm/glm.hpp>

class PointLight
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat quadraticFactor, GLfloat linearFactor, GLfloat constantFactor, glm::vec3 position);
	void UsePointLight(GLuint PointLightQuadraticLocation, GLuint PointLightLinearLocation, 
					GLuint PointLightConstLocation, GLuint PointLightPosLocation, GLuint PointLightColorLocation);
	~PointLight();


private:
	glm::vec3 color;
	GLfloat quadratic, linear, constant;
	glm::vec3 pointLightPosition;
};

