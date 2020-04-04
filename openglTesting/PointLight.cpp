#include "PointLight.h"



PointLight::PointLight(): Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.f;
	linear = 0.0f;
	quadratic = 0.0f;

}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
						GLfloat ambientIntens, GLfloat diffuIntensity,
						GLfloat xPos, GLfloat yPos, GLfloat zPos,
						GLfloat con, GLfloat lin, GLfloat quad) : Light(red, green, blue, ambientIntens, diffuIntensity )
{
	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	linear = lin;
	quadratic = quad;
}

void PointLight::UsePointLight(GLfloat ambientItensityLocation, 
								GLfloat ambientColorLocation, 
								GLfloat diffuseIntensityLocation, 
								GLfloat positionLocation,
								GLfloat constantLocation,
								GLfloat linearLocation,
								GLfloat quadraticLocation)
{
	glUniform1f(ambientItensityLocation, ambientIntensity);
	glUniform3f(ambientColorLocation, color.x, color.y, color.z);	
	glUniform1f(diffuseIntensityLocation, diffuseIntesity);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(quadraticLocation, quadratic);

}

PointLight::~PointLight()
{
}
