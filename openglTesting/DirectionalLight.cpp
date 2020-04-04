#include "DirectionalLight.h"



DirectionalLight::DirectionalLight() : Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}


DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
									GLfloat xDirection, GLfloat yDirection, GLfloat zDirection) 
									: Light(red, green, blue, ambientIntensity, diffuseIntensity)
{
	direction = glm::vec3(xDirection, yDirection, zDirection);
}

void DirectionalLight::UseDirectionalLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform1f(ambientItensityLocation, ambientIntensity);
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntesity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}



DirectionalLight::~DirectionalLight()
{
}
