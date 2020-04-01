#pragma once
#include<glew.h>
#include <glm/glm.hpp>
class SpotLight
{
public:
	SpotLight();
	SpotLight(GLfloat quadraticFactor, GLfloat linearFactor, GLfloat constantFactor, glm::vec3 position);
	~SpotLight();

private:
	GLfloat quadratic, linear, constant;
	glm::vec3 LightPos;
};

