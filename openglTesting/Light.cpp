#include "Light.h"



Light::Light()
{
	// the "amount" of the color
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntesity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntens, GLfloat diffuIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = ambientIntens;

	diffuseIntesity = diffuIntensity;

}

//void Light::UseLight(GLfloat ambientItensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation)
//{	
//	glUniform1f(ambientItensityLocation, ambientIntensity);
//	glUniform3f(ambientColorLocation, color.x, color.y, color.z);
//	glUniform1f(diffuseIntensityLocation, diffuseIntesity);
//	//glUniform3f(directionLocation, direction.x, direction.y, direction.z);
//}


Light::~Light()
{
}
