#include "PointLight.h"


//http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
//100, 1.0, 0.045, 0.0075
PointLight::PointLight()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	constant = 1.0f;
	linear = 0.045f;
	quadratic = 0.0075f;
	pointLightPosition = glm::vec3(0.f, 0.f, 0.f);
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat quadraticFactor, GLfloat linearFactor, GLfloat constantFactor, glm::vec3 position)
{
	color = glm::vec3(red, green, blue);
	constant = 1.0f;
	linear = 0.045f;
	quadratic = 0.0075f;
	pointLightPosition = position;
}

void PointLight::UsePointLight(GLuint PointLightQuadraticLocation, GLuint PointLightLinearLocation, GLuint PointLightConstLocation,
	GLuint PointLightPosLocation, GLuint PointLightColorLocation)
{
	glUniform1f(PointLightQuadraticLocation, quadratic);
	glUniform1f(PointLightLinearLocation, linear);
	glUniform1f(PointLightConstLocation, constant);
	glUniform3f(PointLightPosLocation, pointLightPosition.x, pointLightPosition.y, pointLightPosition.z);
	glUniform3f(PointLightColorLocation, color.x, color.y, color.z);
}


PointLight::~PointLight()
{


}
